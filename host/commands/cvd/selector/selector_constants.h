/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <sys/types.h>

#include <string>

#include "common/libs/utils/result.h"
#include "host/commands/cvd/flag.h"

namespace cuttlefish {
namespace selector {

/** The direct parent of auto-generated runtime directories, which
 * is recommended to be short.
 *
 * Try these one by one in order, and append /.cf
 *
 * 1. $TMPDIR
 * 2. $TEMP
 * 3. $TMP
 * 4. /tmp
 * 5. /var/tmp
 * 6. /usr/tmp
 * 7. HOME of uid
 *
 */
Result<std::string> ParentOfAutogeneratedHomes(const uid_t client_uid,
                                               const gid_t client_gid);

/*
 * These are fields in instance database
 *
 */
constexpr char kGroupNameField[] = "group_name";
constexpr char kHomeField[] = "home";
constexpr char kInstanceIdField[] = "instance_id";
/* per_instance_name
 *
 * by default, to_string(instance_id), and users can override it
 */
constexpr char kInstanceNameField[] = "instance_name";

/**
 * The authentic collection of selector flags
 *
 */
// names of the flags, which are also used for search

class SelectorFlags {
 public:
  static constexpr char kGroupName[] = "group_name";
  static constexpr char kInstanceName[] = "instance_name";
  static constexpr char kAcquireFileLock[] = "acquire_file_lock";
  static constexpr char kAcquireFileLockEnv[] = "CVD_ACQUIRE_FILE_LOCK";
  static constexpr char kDisableDefaultGroup[] = "disable_default_group";
  static const SelectorFlags& Get();

  Result<CvdFlagProxy> GetFlag(const std::string& search_key) const {
    auto flag = CF_EXPECT(flags_.GetFlag(search_key));
    return flag;
  }

  std::vector<CvdFlagProxy> Flags() const { return flags_.Flags(); }

 private:
  SelectorFlags() {
    flags_.EnrollFlag(GroupNameFlag(kGroupName));
    flags_.EnrollFlag(InstanceNameFlag(kInstanceName));
    flags_.EnrollFlag(DisableDefaultGroupFlag(kDisableDefaultGroup, false));
    flags_.EnrollFlag(AcquireFileLockFlag(kAcquireFileLock, true));
  }

  CvdFlag<std::string> GroupNameFlag(const std::string& name);
  CvdFlag<std::string> InstanceNameFlag(const std::string& name);
  CvdFlag<bool> DisableDefaultGroupFlag(const std::string& name,
                                        const bool default_val);
  CvdFlag<bool> AcquireFileLockFlag(const std::string& name,
                                    const bool default_val);

  FlagCollection flags_;
};

}  // namespace selector
}  // namespace cuttlefish
