/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ametsuchi/impl/mutable_storage_impl.hpp>

namespace iroha {
  namespace ametsuchi {

    bool MutableStorageImpl::apply(
        const model::Block &block,
        std::function<bool(const model::Block &, WsvCommand &, WsvQuery &,
                           const model::Block &)>
            function) {
      // TODO replace last arg with previous block
      transaction_->exec("SAVEPOINT savepoint_;");
      auto result = function(block, *executor_, *this, {});
      if (result) {
        transaction_->exec("RELEASE SAVEPOINT savepoint_;");
      } else {
        transaction_->exec("ROLLBACK TO SAVEPOINT savepoint_;");
      }
      return result;
    }

    MutableStorageImpl::MutableStorageImpl(
        std::unique_ptr<FlatFile> &block_store,
        std::unique_ptr<cpp_redis::redis_client> index,
        std::unique_ptr<pqxx::lazyconnection> connection,
        std::unique_ptr<pqxx::nontransaction> transaction,
        std::unique_ptr<WsvQuery> wsv, std::unique_ptr<WsvCommand> executor)
        : block_store_(block_store),
          index_(std::move(index)),
          connection_(std::move(connection)),
          transaction_(std::move(transaction)),
          wsv_(std::move(wsv)),
          executor_(std::move(executor)),
          committed(false) {
      index_->multi();
      transaction_->exec("BEGIN;");
    }

    MutableStorageImpl::~MutableStorageImpl() {
      if (!committed) {
        index_->discard();
        transaction_->exec("ROLLBACK;");
      }
    }

    nonstd::optional<model::Account> MutableStorageImpl::getAccount(
        const std::string &account_id) {
      return wsv_->getAccount(account_id);
    }

    std::vector<ed25519::pubkey_t> MutableStorageImpl::getSignatories(
        const std::string &account_id) {
      return wsv_->getSignatories(account_id);
    }

    nonstd::optional<model::Asset> MutableStorageImpl::getAsset(
        const std::string &asset_id) {
      return wsv_->getAsset(asset_id);
    }

    nonstd::optional<model::AccountAsset> MutableStorageImpl::getAccountAsset(
        const std::string &account_id, const std::string &asset_id) {
      return wsv_->getAccountAsset(account_id, asset_id);
    }

    std::vector<model::Peer> MutableStorageImpl::getPeers() {
      return wsv_->getPeers();
    }
  }  // namespace ametsuchi
}  // namespace iroha