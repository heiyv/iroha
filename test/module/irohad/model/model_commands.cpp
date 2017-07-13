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

#include <commands.pb.h>
#include <gtest/gtest.h>
#include <model/commands/add_asset_quantity.hpp>
#include <model/commands/add_peer.hpp>
#include <crypto/crypto.hpp>

using namespace iroha;

TEST(MODEL_COMMANDS, add_asset_quantity_when_convert_from_proto_to_model) {
  protocol::Command command;
  auto proto_add_asset_quantity = command.add_asset_quantity();
  proto_add_asset_quantity.set_account_id("1");
  proto_add_asset_quantity.set_asset_id("2");
  proto_add_asset_quantity.set_amount("100");

  model::AddAssetQuantity add_asset_quantity(proto_add_asset_quantity);

  ASSERT_EQ(add_asset_quantity.get_account_id(), "1");
  ASSERT_EQ(add_asset_quantity.get_asset_id(), "2");
  ASSERT_EQ(add_asset_quantity.get_amount(), "100");
}

TEST(MODEL_COMMANDS, add_peer_when_convert_from_proto_to_model) {
  protocol::Command command;
  auto proto_add_peer = command.add_peer();
  proto_add_peer.set_address("Innopolis");

  auto seed = iroha::create_seed();
  auto keypair = iroha::create_keypair(seed);
  auto pub_key = keypair.pubkey.to_string();
  proto_add_peer.set_pub_key(pub_key);

  model::AddPeer add_peer(proto_add_peer);

  ASSERT_EQ(add_peer.get_peer().address, "Innopolis");
  ASSERT_EQ(add_peer.get_peer().pubkey, keypair.pubkey);
}