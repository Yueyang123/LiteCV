
#ifndef SEETA_NET_API_H
#define SEETA_NET_API_H

#ifdef SEETANET_STATIC_DEFINE
#  define SEETA_NET_API
#  define SEETANET_NO_EXPORT
#else
#  ifndef SEETA_NET_API
#    ifdef SeetaNet_EXPORTS
        /* We are building this library */
#      define SEETA_NET_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SEETA_NET_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef SEETANET_NO_EXPORT
#    define SEETANET_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef SEETANET_DEPRECATED
#  define SEETANET_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SEETANET_DEPRECATED_EXPORT
#  define SEETANET_DEPRECATED_EXPORT SEETA_NET_API SEETANET_DEPRECATED
#endif

#ifndef SEETANET_DEPRECATED_NO_EXPORT
#  define SEETANET_DEPRECATED_NO_EXPORT SEETANET_NO_EXPORT SEETANET_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define SEETANET_NO_DEPRECATED
#endif

#endif
