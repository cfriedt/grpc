#ifndef GRPC_IMPL_CODEGEN_CLIENT_CONTEXT_H
#define GRPC_IMPL_CODEGEN_CLIENT_CONTEXT_H

//#include <mutex>
#include <string.h>

#include <grpc/impl/codegen/compression_types.h>
#include <grpc/impl/codegen/propagation_bits.h>

struct grpc_server_context;

// A simple array of key-value pairs. May be dynamically allocated
// but does not need to be.
struct grpc_multimap {
    size_t data_size;
    const char **data;
};

struct auth_context {
#if 0
    const grpc_auth_property* property_;
    // The following items form a grpc_auth_property_iterator.
    const grpc_auth_context* ctx_;
    size_t index_;
    const char* name_;
#endif
};

typedef enum {
    RPC_TYPE_NORMAL_RPC,
    RPC_TYPE_CLIENT_STREAMING,
    RPC_TYPE_SERVER_STREAMING,
    RPC_TYPE_BIDI_STREAMING,
} rpc_type;

struct client_rpc_info {
    struct grpc_client_context* ctx;
    rpc_type type;
    const char* method;
    grpc_channel* channel;
};

struct grpc_client_context {

  bool initial_metadata_received_;
  bool wait_for_ready_;
  bool wait_for_ready_explicitly_set_;
  bool idempotent_;
  bool cacheable_;
  grpc_channel* channel_;
  //std::mutex mu_;
  grpc_call* call_;
  bool call_canceled_;
  gpr_timespec deadline_;
  const char* authority_;
  struct call_credentials* creds_;
  struct auth_context* auth_context_;
  struct census_context* census_context_;
  struct grpc_multimap send_initial_metadata_;
  struct grpc_multimap recv_initial_metadata_;
  struct grpc_multimap trailing_metadata_;

  grpc_call* propagate_from_call_;
  uint32_t propagation_options_;

  grpc_compression_algorithm compression_algorithm_;
  bool initial_metadata_corked_;

  char *debug_error_string_;

  struct client_rpc_info rpc_info_;
};

// "static" method
static inline struct grpc_client_context
grpc_client_context_FromServerContext( const struct grpc_server_context* server_context, uint32_t options) {
    (void) server_context;
    (void) options;
    struct grpc_client_context r = {0};
    return r;
}

#if 0
struct global_callbacks {
};
static inline void grpc_client_context_SetGlobalCallbacks(struct global_calbacks* callbacks) {
}
#endif

static inline void
grpc_client_context_AddMetadata(struct grpc_client_context* client_context, const char* meta_key, const char* meta_value) {
    (void) client_context;
    (void) meta_key;
    (void) meta_value;
}

static inline struct grpc_multimap
grpc_client_context_GetServerInitialMetadata(struct grpc_client_context* client_context) {
    (void) client_context;
    struct grpc_multimap r = {0};
    return r;
}

static inline struct grpc_multimap
grpc_client_context_GetServerTrailingMetadata(struct grpc_client_context* client_context) {
    (void) client_context;
    struct grpc_multimap r = {0};
    return r;
}

static inline void
grpc_client_context_SetDeadline(struct grpc_client_context* client_context, const gpr_timespec* deadline) {
    (void) client_context;
    (void) deadline;
}

// experimental
#if 0
static inline void
grpc_client_context_SetIdempotent(struct grpc_client_context* client_context, bool idempotent) {
    (void) client_context;
    (void) idempotent;
}
#endif

// experimental
#if 0
static inline void
grpc_client_context_SetCacheable(struct grpc_client_context* client_context, bool cacheable) {
    (void) client_context;
    (void) cacheable;
}
#endif

// experimental
#if 0
static inline void
grpc_client_context_SetWaitForReady(struct grpc_client_context* client_context, bool wait_for_ready) {
    (void) client_context;
    (void) wait_for_ready;
    // wait_for_ready_explicitly_set = true;
}
#endif

// deprecated
#if 0
static inline void
grpc_client_context_SetFailFast(struct grpc_client_context* client_context, bool fail_fast) {
    grpc_client_context_SetWaitForReady(client_context, !fail_fast);
}
#endif

static inline gpr_timespec
grpc_client_context_TimePointDeadline(struct grpc_client_context* client_context) {
    return client_context->deadline_;
}

static inline gpr_timespec
grpc_client_context_RawDeadline(struct grpc_client_context* client_context) {
    return grpc_client_context_TimePointDeadline(client_context);
}

static inline void
grpc_client_context_SetAuthority(struct grpc_client_context* client_context, const char *authority) {
    (void) client_context;
    (void) authority;
}

static inline struct auth_context
grpc_client_context_AuthContext(struct grpc_client_context* client_context) {
    (void) client_context;
    struct auth_context r = {};
    return r;
}

struct call_credentials;
static inline void
grpc_client_context_SetCredentials(struct grpc_client_context* client_context, struct call_credentials *creds) {
    (void) client_context;
    (void) creds;
}

static inline grpc_compression_algorithm
grpc_client_context_CompressionAlgorithm(struct grpc_client_context* client_context) {
    (void) client_context;
    return GRPC_COMPRESS_NONE;
}

static inline void
grpc_client_context_SetCompressionAlgorithm(struct grpc_client_context* client_context, grpc_compression_algorithm algorithm) {
    (void) client_context;
    (void) algorithm;
}

static inline void
grpc_client_context_SetInitialMetadataCorked(struct grpc_client_context* client_context, bool corked) {
    (void) client_context;
    (void) corked;
}

static inline const char*
grpc_client_context_Peer(struct grpc_client_context* client_context) {
    (void) client_context;
    return "";
}

static inline void
grpc_client_context_SetCensusContext(struct grpc_client_context* client_context, struct census_context* ccp) {
    (void) client_context;
    (void) ccp;
}

static inline void
grpc_client_context_TryCancel(struct grpc_client_context* client_context) {
    (void) client_context;
}

static inline const char*
grpc_client_context_DebugErrorString(struct grpc_client_context* client_context) {
    (void) client_context;
    return NULL;
}

static inline void
grpc_client_context_SetDebugErrorString(struct grpc_client_context* client_context, const char *debug_error_string) {
    (void) client_context;
    (void) debug_error_string;
}

static inline grpc_call*
grpc_client_context_Call(struct grpc_client_context* client_context) {
    (void) client_context;
    return NULL;
}

static inline void
grpc_client_context_SetCall(struct grpc_client_context* client_context, grpc_call *call, grpc_channel *channel) {
    (void) client_context;
    (void) call;
    (void) channel;
}

static inline struct client_rpc_info*
grpc_client_context_SetClientRpcInfo(struct grpc_client_context* client_context, const char*method, rpc_type type, grpc_channel* channel) {
    (void) client_context;
    (void) method;
    (void) type;
    (void) channel;
    return NULL;
}

static inline uint32_t
grpc_client_context_InitialMetadataFlags(struct grpc_client_context* client_context) {
    return (client_context->idempotent_ ? GRPC_INITIAL_METADATA_IDEMPOTENT_REQUEST : 0) |
           (client_context->wait_for_ready_ ? GRPC_INITIAL_METADATA_WAIT_FOR_READY : 0) |
           (client_context->cacheable_ ? GRPC_INITIAL_METADATA_CACHEABLE_REQUEST : 0) |
           (client_context->wait_for_ready_explicitly_set_
                ? GRPC_INITIAL_METADATA_WAIT_FOR_READY_EXPLICITLY_SET
                : 0) |
           (client_context->initial_metadata_corked_ ? GRPC_INITIAL_METADATA_CORKED : 0);
}

static inline const char*
grpc_client_context_Authority(struct grpc_client_context* client_context) {
    (void) client_context;
    return NULL;
}

#endif  /* GRPC_IMPL_CODEGEN_CLIENT_CONTEXT_H */
