/*
 * Copyright (C) 2016 The Android Open Source Project
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
#ifndef GCE_METADATA_QUERY_H_
#define GCE_METADATA_QUERY_H_

static const int kMaxMetadataResponseBufferSize = 65536;

class AutoCloseFileDescriptor;
class AutoFreeBuffer;

class MetadataQuery {
 public:
  virtual ~MetadataQuery() {}

  // Request metadata from the server.
  // On success returns true, and current metadata in supplied buffer.
  virtual bool QueryServer(AutoFreeBuffer* buffer) = 0;

  static MetadataQuery* New();
};

#endif  // GCE_METADATA_QUERY_H_
