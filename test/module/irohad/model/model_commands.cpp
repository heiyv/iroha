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

#include <gtest/gtest.h>
#include <model/commands/add_asset_quantity.hpp>
#include <commands.pb.h>

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