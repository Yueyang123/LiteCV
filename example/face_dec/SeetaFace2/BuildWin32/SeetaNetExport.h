
#ifndef SEETA_NET_API_H
#define SEETA_NET_API_H

#ifdef SEETANET_STATIC_DEFINE
#  define SEETA_NET_API
#  define SEETANET_NO_EXPORT
#else
#  ifndef SEETA_NET_API
#    ifdef SeetaNet_EXPORTS
        /* We are building this library */
#      define SEETA_NET_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define SEETA_NET_API __declspec(dllimport)
#    endif
#  endif

#  ifndef SEETANET_NO_EXPORT
#    define SEETANET_NO_EXPORT 
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

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SEETANET_NO_DEPRECATED
#    define SEETANET_NO_DEPRECATED
#  endif
#endif

#endif /* SEETA_NET_API_H */
