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

#ifndef IROHA_MUTABLE_STORAGE_IMPL_HPP
#define IROHA_MUTABLE_STORAGE_IMPL_HPP

#include <ametsuchi/impl/flat_file/flat_file.hpp>
#include <ametsuchi/mutable_storage.hpp>
#include <cpp_redis/redis_client.hpp>
#include <pqxx/nontransaction>

namespace iroha {
  namespace ametsuchi {
    class MutableStorageImpl : public MutableStorage {
      friend class StorageImpl;

     public:
      MutableStorageImpl(std::unique_ptr<FlatFile> &block_store,
                         std::unique_ptr<cpp_redis::redis_client> index,
                         std::unique_ptr<pqxx::nontransaction> transaction,
                         std::unique_ptr<WsvQuery> wsv,
                         std::unique_ptr<WsvCommand> executor);
      bool apply(const model::Block &block,
                 std::function<bool(const model::Block &, WsvCommand &,
                                    WsvQuery &, const model::Block &)>
                     function) override;
      ~MutableStorageImpl() override;
      nonstd::optional<model::Account> getAccount(const std::string &account_id) override;
      std::vector<ed25519::pubkey_t> getSignatories(const std::string &account_id) override;
      nonstd::optional<model::Asset> getAsset(const std::string &asset_id) override;
      nonstd::optional<model::AccountAsset> getAccountAsset(const std::string &account_id,
                                          const std::string &asset_id) override;
      nonstd::optional<model::Peer> getPeer(const std::string &address) override;

     private:
      std::unique_ptr<FlatFile> &block_store_;
      std::unique_ptr<cpp_redis::redis_client> index_;

      std::unique_ptr<pqxx::nontransaction> transaction_;
      std::unique_ptr<WsvQuery> wsv_;
      std::unique_ptr<WsvCommand> executor_;

      bool committed;
    };
  }  // namespace ametsuchi
}  // namespace iroha

#endif  // IROHA_MUTABLE_STORAGE_IMPL_HPP
