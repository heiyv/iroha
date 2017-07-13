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

#include <model/commands/add_asset_quantity.hpp>
#include <model/commands/add_peer.hpp>

namespace iroha {
  namespace model {

    /* AddAssetQuantity */
    AddAssetQuantity::AddAssetQuantity(
        protocol::AddAssetQuantity proto_add_asset_quantity) {
      account_id = proto_add_asset_quantity.account_id();
      asset_id = proto_add_asset_quantity.asset_id();
      amount = proto_add_asset_quantity.amount();
    }

    std::string AddAssetQuantity::get_account_id() { return account_id; }

    std::string AddAssetQuantity::get_asset_id() { return asset_id; }

    std::string AddAssetQuantity::get_amount() { return amount; }

    bool AddAssetQuantity::validate(ametsuchi::WsvQuery &queries,
                                    const Account &creator) {
      return true;
    }

    bool AddAssetQuantity::execute(ametsuchi::WsvQuery &queries,
                                   ametsuchi::WsvCommand &commands) {
      return true;
    }

    /* AddPeer */

    AddPeer::AddPeer(protocol::AddPeer &proto_add_peer) {
      auto res = base64_decode(proto_add_peer.pub_key());
      std::copy(proto_add_peer.pub_key().begin(),
                proto_add_peer.pub_key().end(), peer.pubkey.data());
      peer.address = proto_add_peer.address();
    }

    Peer AddPeer::get_peer() { return peer; }

    bool AddPeer::validate(ametsuchi::WsvQuery &queries,
                           const Account &creator) {
      return true;
    }

    bool AddPeer::execute(ametsuchi::WsvQuery &queries,
                          ametsuchi::WsvCommand &commands) {
      return true;
    }
  }
}