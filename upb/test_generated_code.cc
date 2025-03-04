/*
 * Copyright (c) 2009-2021, Google LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Google LLC nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL Google LLC BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Test of generated code, with a special focus on features that are not used in
 * descriptor.proto or conformance.proto (since these get some testing from
 * upb/def.c and tests/conformance_upb.c, respectively).
 */

#include "gtest/gtest.h"
#include "src/google/protobuf/test_messages_proto3.upb.h"
#include "upb/test.upb.h"
#include "upb/upb.hpp"

#if !defined(MIN)
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#endif

const char test_str[] = "abcdefg";
const char test_str2[] = "12345678910";
const char test_str3[] = "rstlnezxcvbnm";
const char test_str4[] = "just another test string";

const upb_StringView test_str_view = {test_str, sizeof(test_str) - 1};
const upb_StringView test_str_view2 = {test_str2, sizeof(test_str2) - 1};
const upb_StringView test_str_view3 = {test_str3, sizeof(test_str3) - 1};
const upb_StringView test_str_view4 = {test_str4, sizeof(test_str4) - 1};

const int32_t test_int32 = 10;
const int32_t test_int32_2 = -20;
const int32_t test_int32_3 = 30;
const int32_t test_int32_4 = -40;

TEST(GeneratedCode, Scalars) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(arena);
  protobuf_test_messages_proto3_TestAllTypesProto3* msg2;
  upb_StringView serialized;
  upb_StringView val;

  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_int32(msg, 10);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_int64(msg, 20);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_uint32(msg, 30);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_uint64(msg, 40);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_float(msg,
                                                                      50.5);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_double(msg,
                                                                       60.6);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_bool(msg, 1);
  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_string(
      msg, test_str_view);

  serialized.data = protobuf_test_messages_proto3_TestAllTypesProto3_serialize(
      msg, arena, &serialized.size);

  msg2 = protobuf_test_messages_proto3_TestAllTypesProto3_parse(
      serialized.data, serialized.size, arena);

  EXPECT_EQ(10, protobuf_test_messages_proto3_TestAllTypesProto3_optional_int32(
                    msg2));
  EXPECT_EQ(20, protobuf_test_messages_proto3_TestAllTypesProto3_optional_int64(
                    msg2));
  EXPECT_EQ(
      30,
      protobuf_test_messages_proto3_TestAllTypesProto3_optional_uint32(msg2));
  EXPECT_EQ(
      40,
      protobuf_test_messages_proto3_TestAllTypesProto3_optional_uint64(msg2));
  EXPECT_EQ(
      50.5,
      protobuf_test_messages_proto3_TestAllTypesProto3_optional_float(msg2));
  EXPECT_EQ(
      60.6,
      protobuf_test_messages_proto3_TestAllTypesProto3_optional_double(msg2));
  EXPECT_EQ(
      true,
      protobuf_test_messages_proto3_TestAllTypesProto3_optional_bool(msg2));
  val = protobuf_test_messages_proto3_TestAllTypesProto3_optional_string(msg2);
  EXPECT_TRUE(upb_StringView_IsEqual(val, test_str_view));

  upb_Arena_Free(arena);
}

TEST(GeneratedCode, UTF8) {
  const char invalid_utf8[] = "\xff";
  const upb_StringView invalid_utf8_view =
      upb_StringView_FromDataAndSize(invalid_utf8, 1);
  upb_Arena* arena = upb_Arena_New();
  upb_StringView serialized;
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(arena);
  protobuf_test_messages_proto3_TestAllTypesProto3* msg2;

  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_string(
      msg, invalid_utf8_view);

  serialized.data = protobuf_test_messages_proto3_TestAllTypesProto3_serialize(
      msg, arena, &serialized.size);

  msg2 = protobuf_test_messages_proto3_TestAllTypesProto3_parse(
      serialized.data, serialized.size, arena);
  EXPECT_EQ(nullptr, msg2);

  upb_Arena_Free(arena);
}

static void check_string_map_empty(
    protobuf_test_messages_proto3_TestAllTypesProto3* msg) {
  size_t iter = kUpb_Map_Begin;

  EXPECT_EQ(
      0,
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_size(
          msg));
  EXPECT_FALSE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_next(
          msg, &iter));
}

static void check_string_map_one_entry(
    protobuf_test_messages_proto3_TestAllTypesProto3* msg) {
  const protobuf_test_messages_proto3_TestAllTypesProto3_MapStringStringEntry*
      const_ent;
  size_t iter;
  upb_StringView str;

  EXPECT_EQ(
      1,
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_size(
          msg));
  EXPECT_TRUE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_get(
          msg, test_str_view, &str));
  EXPECT_TRUE(upb_StringView_IsEqual(str, test_str_view2));

  EXPECT_FALSE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_get(
          msg, test_str_view3, &str));

  /* Test that iteration reveals a single k/v pair in the map. */
  iter = kUpb_Map_Begin;
  const_ent =
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_next(
          msg, &iter);
  ASSERT_NE(nullptr, const_ent);
  EXPECT_TRUE(upb_StringView_IsEqual(
      test_str_view,
      protobuf_test_messages_proto3_TestAllTypesProto3_MapStringStringEntry_key(
          const_ent)));
  EXPECT_TRUE(upb_StringView_IsEqual(
      test_str_view2,
      protobuf_test_messages_proto3_TestAllTypesProto3_MapStringStringEntry_value(
          const_ent)));

  const_ent =
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_next(
          msg, &iter);
  EXPECT_EQ(nullptr, const_ent);
}

TEST(GeneratedCode, StringDoubleMap) {
  upb_Arena* arena = upb_Arena_New();
  upb_StringView serialized;
  upb_test_MapTest* msg = upb_test_MapTest_new(arena);
  upb_test_MapTest* msg2;
  double val;

  upb_test_MapTest_map_string_double_set(msg, test_str_view, 1.5, arena);
  ASSERT_NE(nullptr, msg);
  EXPECT_TRUE(upb_test_MapTest_map_string_double_get(msg, test_str_view, &val));
  EXPECT_EQ(1.5, val);
  val = 0;

  serialized.data = upb_test_MapTest_serialize(msg, arena, &serialized.size);
  EXPECT_NE(nullptr, serialized.data);

  msg2 = upb_test_MapTest_parse(serialized.data, serialized.size, arena);
  ASSERT_NE(nullptr, msg2);
  EXPECT_TRUE(
      upb_test_MapTest_map_string_double_get(msg2, test_str_view, &val));
  EXPECT_EQ(1.5, val);

  upb_Arena_Free(arena);
}

TEST(GeneratedCode, StringMap) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(arena);
  const protobuf_test_messages_proto3_TestAllTypesProto3_MapStringStringEntry*
      const_ent;
  size_t iter, count;

  check_string_map_empty(msg);

  /* Set map[test_str_view] = test_str_view2 */
  protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_set(
      msg, test_str_view, test_str_view2, arena);
  check_string_map_one_entry(msg);

  /* Deleting a non-existent key does nothing. */
  EXPECT_FALSE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_delete(
          msg, test_str_view3));
  check_string_map_one_entry(msg);

  /* Deleting the key sets the map back to empty. */
  EXPECT_TRUE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_delete(
          msg, test_str_view));
  check_string_map_empty(msg);

  /* Set two keys this time:
   *   map[test_str_view] = test_str_view2
   *   map[test_str_view3] = test_str_view4
   */
  protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_set(
      msg, test_str_view, test_str_view2, arena);
  protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_set(
      msg, test_str_view3, test_str_view4, arena);

  /* Test iteration */
  iter = kUpb_Map_Begin;
  count = 0;

  while (
      (const_ent =
           protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_next(
               msg, &iter)) != NULL) {
    upb_StringView key =
        protobuf_test_messages_proto3_TestAllTypesProto3_MapStringStringEntry_key(
            const_ent);
    upb_StringView val =
        protobuf_test_messages_proto3_TestAllTypesProto3_MapStringStringEntry_value(
            const_ent);

    count++;
    if (upb_StringView_IsEqual(key, test_str_view)) {
      EXPECT_TRUE(upb_StringView_IsEqual(val, test_str_view2));
    } else {
      EXPECT_TRUE(upb_StringView_IsEqual(key, test_str_view3));
      EXPECT_TRUE(upb_StringView_IsEqual(val, test_str_view4));
    }
  }

  EXPECT_EQ(2, count);

  /* Clearing the map goes back to empty. */
  protobuf_test_messages_proto3_TestAllTypesProto3_map_string_string_clear(msg);
  check_string_map_empty(msg);

  upb_Arena_Free(arena);
}

static void check_int32_map_empty(
    protobuf_test_messages_proto3_TestAllTypesProto3* msg) {
  size_t iter = kUpb_Map_Begin;

  EXPECT_EQ(
      0, protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_size(
             msg));
  EXPECT_FALSE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_next(
          msg, &iter));
}

static void check_int32_map_one_entry(
    protobuf_test_messages_proto3_TestAllTypesProto3* msg) {
  const protobuf_test_messages_proto3_TestAllTypesProto3_MapInt32Int32Entry*
      const_ent;
  size_t iter;
  int32_t val;

  EXPECT_EQ(
      1, protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_size(
             msg));
  EXPECT_TRUE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_get(
          msg, test_int32, &val));
  EXPECT_EQ(val, test_int32_2);

  EXPECT_FALSE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_get(
          msg, test_int32_3, &val));

  /* Test that iteration reveals a single k/v pair in the map. */
  iter = kUpb_Map_Begin;
  const_ent =
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_next(
          msg, &iter);
  ASSERT_NE(nullptr, const_ent);
  EXPECT_EQ(
      test_int32,
      protobuf_test_messages_proto3_TestAllTypesProto3_MapInt32Int32Entry_key(
          const_ent));
  EXPECT_EQ(
      test_int32_2,
      protobuf_test_messages_proto3_TestAllTypesProto3_MapInt32Int32Entry_value(
          const_ent));

  const_ent =
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_next(
          msg, &iter);
  EXPECT_EQ(nullptr, const_ent);
}

TEST(GeneratedCode, Int32Map) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(arena);
  const protobuf_test_messages_proto3_TestAllTypesProto3_MapInt32Int32Entry*
      const_ent;
  size_t iter, count;

  check_int32_map_empty(msg);

  /* Set map[test_int32] = test_int32_2 */
  protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_set(
      msg, test_int32, test_int32_2, arena);
  check_int32_map_one_entry(msg);

  /* Deleting a non-existent key does nothing. */
  EXPECT_FALSE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_delete(
          msg, test_int32_3));
  check_int32_map_one_entry(msg);

  /* Deleting the key sets the map back to empty. */
  EXPECT_TRUE(
      protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_delete(
          msg, test_int32));
  check_int32_map_empty(msg);

  /* Set two keys this time:
   *   map[test_int32] = test_int32_2
   *   map[test_int32_3] = test_int32_4
   */
  protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_set(
      msg, test_int32, test_int32_2, arena);
  protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_set(
      msg, test_int32_3, test_int32_4, arena);

  /* Test iteration */
  iter = kUpb_Map_Begin;
  count = 0;

  while (
      (const_ent =
           protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_next(
               msg, &iter)) != NULL) {
    int32_t key =
        protobuf_test_messages_proto3_TestAllTypesProto3_MapInt32Int32Entry_key(
            const_ent);
    int32_t val =
        protobuf_test_messages_proto3_TestAllTypesProto3_MapInt32Int32Entry_value(
            const_ent);

    count++;
    if (key == test_int32) {
      EXPECT_EQ(val, test_int32_2);
    } else {
      EXPECT_EQ(key, test_int32_3);
      EXPECT_EQ(val, test_int32_4);
    }
  }

  EXPECT_EQ(2, count);

  /* Clearing the map goes back to empty. */
  protobuf_test_messages_proto3_TestAllTypesProto3_map_int32_int32_clear(msg);
  check_int32_map_empty(msg);

  upb_Arena_Free(arena);
}

TEST(GeneratedCode, TestRepeated) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(arena);
  size_t size;
  const int* elems;

  protobuf_test_messages_proto3_TestAllTypesProto3_add_repeated_int32(msg, 5,
                                                                      arena);

  elems = protobuf_test_messages_proto3_TestAllTypesProto3_repeated_int32(
      msg, &size);

  EXPECT_EQ(1, size);
  EXPECT_EQ(5, elems[0]);

  upb_Arena_Free(arena);
}

TEST(GeneratedCode, Issue9440) {
  upb::Arena arena;
  upb_test_HelloRequest* msg = upb_test_HelloRequest_new(arena.ptr());
  upb_test_HelloRequest_set_id(msg, 8);
  EXPECT_EQ(8, upb_test_HelloRequest_id(msg));
  char str[] = "1";
  upb_test_HelloRequest_set_version(msg, upb_StringView{str, strlen(str)});
  EXPECT_EQ(8, upb_test_HelloRequest_id(msg));
}

TEST(GeneratedCode, NullDecodeBuffer) {
  upb_Arena* arena = upb_Arena_New();
  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_parse(NULL, 0, arena);
  size_t size;

  ASSERT_NE(nullptr, msg);
  protobuf_test_messages_proto3_TestAllTypesProto3_serialize(msg, arena, &size);
  EXPECT_EQ(0, size);
  upb_Arena_Free(arena);
}

TEST(GeneratedCode, StatusTruncation) {
  int i, j;
  upb_Status status;
  upb_Status status2;
  for (i = 0; i < _kUpb_Status_MaxMessage + 20; i++) {
    char* msg = static_cast<char*>(malloc(i + 1));
    int end;
    char ch = (i % 96) + 33; /* Cycle through printable chars. */

    for (j = 0; j < i; j++) {
      msg[j] = ch;
    }
    msg[i] = '\0';

    upb_Status_SetErrorMessage(&status, msg);
    upb_Status_SetErrorFormat(&status2, "%s", msg);
    end = MIN(i, _kUpb_Status_MaxMessage - 1);
    EXPECT_EQ(end, strlen(status.msg));
    EXPECT_EQ(end, strlen(status2.msg));

    for (j = 0; j < end; j++) {
      EXPECT_EQ(ch, status.msg[j]);
      EXPECT_EQ(ch, status2.msg[j]);
    }

    free(msg);
  }
}

static void decrement_int(void* ptr) {
  int* iptr = static_cast<int*>(ptr);
  (*iptr)--;
}

TEST(GeneratedCode, ArenaFuse) {
  int i1 = 5;
  int i2 = 5;
  int i3 = 5;
  int i4 = 5;

  upb_Arena* arena1 = upb_Arena_New();
  upb_Arena* arena2 = upb_Arena_New();

  upb_Arena_AddCleanup(arena1, &i1, decrement_int);
  upb_Arena_AddCleanup(arena2, &i2, decrement_int);

  EXPECT_TRUE(upb_Arena_Fuse(arena1, arena2));

  upb_Arena_AddCleanup(arena1, &i3, decrement_int);
  upb_Arena_AddCleanup(arena2, &i4, decrement_int);

  upb_Arena_Free(arena1);
  EXPECT_EQ(5, i1);
  EXPECT_EQ(5, i2);
  EXPECT_EQ(5, i3);
  EXPECT_EQ(5, i4);
  upb_Arena_Free(arena2);
  EXPECT_EQ(4, i1);
  EXPECT_EQ(4, i2);
  EXPECT_EQ(4, i3);
  EXPECT_EQ(4, i4);
}

/* Do nothing allocator for testing */
static void* test_allocfunc(upb_alloc* alloc, void* ptr, size_t oldsize,
                            size_t size) {
  return upb_alloc_global.func(alloc, ptr, oldsize, size);
}
upb_alloc test_alloc = {&test_allocfunc};

TEST(GeneratedCode, FuseWithInitialBlock) {
  char buf1[1024];
  char buf2[1024];
  upb_Arena* arenas[] = {upb_Arena_Init(buf1, 1024, &upb_alloc_global),
                         upb_Arena_Init(buf2, 1024, &upb_alloc_global),
                         upb_Arena_Init(NULL, 0, &test_alloc),
                         upb_Arena_Init(NULL, 0, &upb_alloc_global)};
  int size = sizeof(arenas) / sizeof(arenas[0]);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i == j) {
        EXPECT_TRUE(upb_Arena_Fuse(arenas[i], arenas[j]));
      } else {
        EXPECT_FALSE(upb_Arena_Fuse(arenas[i], arenas[j]));
      }
    }
  }

  for (int i = 0; i < size; ++i) upb_Arena_Free(arenas[i]);
}

TEST(GeneratedCode, ArenaDecode) {
  // Tests against a bug that previously existed when passing an arena to
  // upb_decode().
  char large_string[1024] = {0};
  upb_StringView large_string_view = {large_string, sizeof(large_string)};
  upb_Arena* tmp = upb_Arena_New();

  protobuf_test_messages_proto3_TestAllTypesProto3* msg =
      protobuf_test_messages_proto3_TestAllTypesProto3_new(tmp);

  protobuf_test_messages_proto3_TestAllTypesProto3_set_optional_bytes(
      msg, large_string_view);

  upb_StringView serialized;
  serialized.data = protobuf_test_messages_proto3_TestAllTypesProto3_serialize(
      msg, tmp, &serialized.size);

  upb_Arena* arena = upb_Arena_New();
  // Parse the large payload, forcing an arena block to be allocated. This used
  // to corrupt the cleanup list, preventing subsequent upb_Arena_AddCleanup()
  // calls from working properly.
  protobuf_test_messages_proto3_TestAllTypesProto3_parse(
      serialized.data, serialized.size, arena);

  int i1 = 5;
  upb_Arena_AddCleanup(arena, &i1, decrement_int);
  EXPECT_EQ(5, i1);
  upb_Arena_Free(arena);
  EXPECT_EQ(4, i1);

  upb_Arena_Free(tmp);
}

TEST(GeneratedCode, ArenaUnaligned) {
  char buf1[1024];
  // Force the pointer to be unaligned.
  char* unaligned_buf_ptr = (char*)((uintptr_t)buf1 | 7);
  upb_Arena* arena = upb_Arena_Init(
      unaligned_buf_ptr, &buf1[sizeof(buf1)] - unaligned_buf_ptr, NULL);
  char* mem = static_cast<char*>(upb_Arena_Malloc(arena, 5));
  EXPECT_EQ(0, reinterpret_cast<uintptr_t>(mem) & 15);
  upb_Arena_Free(arena);

  // Try the same, but with a size so small that aligning up will overflow.
  arena = upb_Arena_Init(unaligned_buf_ptr, 5, &upb_alloc_global);
  mem = static_cast<char*>(upb_Arena_Malloc(arena, 5));
  EXPECT_EQ(0, reinterpret_cast<uintptr_t>(mem) & 15);
  upb_Arena_Free(arena);
}
