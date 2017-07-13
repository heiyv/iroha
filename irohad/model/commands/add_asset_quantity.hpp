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

#ifndef IROHA_ISSUE_ASSET_HPP
#define IROHA_ISSUE_ASSET_HPP

#include <model/command.hpp>
#include <string>
#include <commands.pb.h>

namespace iroha {
  namespace model {

    /**
     * Add amount of asset to an account
     */
    class AddAssetQuantity : public Command {
     public:

      explicit AddAssetQuantity(protocol::AddAssetQuantity proto_add_asset_quantity);

      bool validate(ametsuchi::WsvQuery& queries,
                    const Account& creator) override;
      bool execute(ametsuchi::WsvQuery& queries,
                   ametsuchi::WsvCommand& commands) override;

      std::string get_account_id();
      std::string get_asset_id();
      std::string get_amount();

     private:
      /**
       * Account where to add assets
       */
      std::string account_id;

      /**
       * Asset to issue
       * Note: must exist in the system
       */
      std::string asset_id;

      /**
       * Amount to add to wallet
       */
      std::string amount;
    };
  }  // namespace model
}  // namespace iroha
#endif  // IROHA_ISSUE_ASSET_HPP
