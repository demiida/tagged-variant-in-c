// 256 個以下の型のタグ付き直和型を実装できます
#pragma once
#include <stdint.h>
#include "foreach-va-args.h"

#define VARIANT_UNION_MEMBER_IDENT(Type) As_##Type
#define VARIANT_CONSTRUCT_UNION_MEMBER(Type) \
  Type VARIANT_UNION_MEMBER_IDENT(Type);

#define VARIANT_DEFINE(Variant, ...)                               \
  typedef struct {                                                 \
    enum : uint8_t {                                               \
      ADD_PREFIX_FOREACH_VA_ARGS(Variant##_, __VA_ARGS__)          \
    } tag;                                                         \
    union {                                                        \
      FOREACH_VA_ARGS(VARIANT_CONSTRUCT_UNION_MEMBER, __VA_ARGS__) \
    };                                                             \
  } Variant

#define VARIANT_TAG(Variant, Type) Variant##_##Type
#define VARIANT_WRAP(Variant, Type, data)        \
  ((Variant) {.tag = VARIANT_TAG(Variant, Type), \
              .VARIANT_UNION_MEMBER_IDENT(Type) = data})
#define VARIANT_UNWRAP(variant, Type) (variant.VARIANT_UNION_MEMBER_IDENT(Type))
