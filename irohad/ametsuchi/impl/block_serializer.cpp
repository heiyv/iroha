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

#include <ametsuchi/block_serializer.hpp>
#include <model/commands/add_peer.hpp>
#include <model/commands/add_asset_quantity.hpp>
#include <iostream>

namespace iroha {
  namespace ametsuchi {

    using namespace rapidjson;

    void BlockSerializer::serialize(PrettyWriter<StringBuffer>& writer,
                                    model::Block block) {
      writer.StartObject();
      writer.String("hash");
      writer.String(block.hash.to_string().c_str());

      writer.String("signatures");
      writer.StartArray();
      for (auto sig : block.sigs) {
        serialize(writer, sig);
      }
      writer.EndArray();

      writer.String("created_ts");
      writer.Uint64(block.created_ts);

      writer.String("height");
      writer.Uint64(block.height);

      writer.String("prev_hash");
      writer.String(block.prev_hash.to_string().c_str());

      writer.String("txs_number");
      writer.Uint(block.txs_number);

      writer.String("merkle_root");
      writer.String(block.merkle_root.to_string().c_str());

      writer.String("transactions");
      writer.StartArray();
      for (auto tx : block.transactions) {
        serialize(writer, tx);
      }
      writer.EndArray();

      writer.EndObject();
    }

    void BlockSerializer::serialize(PrettyWriter<StringBuffer>& writer,
                                    model::Signature signature) {
      writer.StartObject();

      writer.String("pubkey");
      writer.String(signature.pubkey.to_string().c_str());

      writer.String("signature");
      writer.String(signature.signature.to_string().c_str());

      writer.EndObject();
    }

    void BlockSerializer::serialize(PrettyWriter<StringBuffer>& writer,
                                    model::Transaction transaction) {
      writer.StartObject();

      writer.String("signatures");
      writer.StartArray();
      for (auto sig : transaction.signatures) {
        serialize(writer, sig);
      }
      writer.EndArray();

      writer.String("created_ts");
      writer.Uint64(transaction.created_ts);

      writer.String("creator_account_id");
      writer.String(transaction.creator_account_id.c_str());

      writer.String("tx_counter");
      writer.Uint64(transaction.tx_counter);

      writer.String("commands");
      writer.StartArray();
      for (auto command: transaction.commands){
        serialize(writer, *command);
      }
      writer.EndArray();

      writer.EndObject();
    }

    void BlockSerializer::serialize(PrettyWriter<StringBuffer>& writer,
                                    model::Command& command) {
      if (instanceof<model::AddPeer>(&command)){
        auto add_peer = static_cast<model::AddPeer&>(command);
        writer.StartObject();

        writer.String("command_type");
        writer.String("AddPeer");

        writer.String("address");
        writer.String(add_peer.address.c_str());

        writer.String("peer_key");
        writer.String(add_peer.peer_key.to_string().c_str());

        writer.EndObject();
      }
      if (instanceof<model::AddAssetQuantity>(&command)){
        auto add_asset_quantity = static_cast<model::AddAssetQuantity&>(command);
        writer.StartObject();

        writer.String("command_type");
        writer.String("AddAssetQuantity");

        writer.String("account_id");
        writer.String(add_asset_quantity.account_id.c_str());

        writer.String("asset_id");
        writer.String(add_asset_quantity.asset_id.c_str());


        writer.String("amount");
      }
    }
  }
}