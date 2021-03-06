
#ifndef SEETA_RECOGNIZER_API_H
#define SEETA_RECOGNIZER_API_H

#ifdef SEETAFACERECOGNIZER_STATIC_DEFINE
#  define SEETA_RECOGNIZER_API
#  define SEETAFACERECOGNIZER_NO_EXPORT
#else
#  ifndef SEETA_RECOGNIZER_API
#    ifdef SeetaFaceRecognizer_EXPORTS
        /* We are building this library */
#      define SEETA_RECOGNIZER_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define SEETA_RECOGNIZER_API __declspec(dllimport)
#    endif
#  endif

#  ifndef SEETAFACERECOGNIZER_NO_EXPORT
#    define SEETAFACERECOGNIZER_NO_EXPORT 
#  endif
#endif

#ifndef SEETAFACERECOGNIZER_DEPRECATED
#  define SEETAFACERECOGNIZER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SEETAFACERECOGNIZER_DEPRECATED_EXPORT
#  define SEETAFACERECOGNIZER_DEPRECATED_EXPORT SEETA_RECOGNIZER_API SEETAFACERECOGNIZER_DEPRECATED
#endif

#ifndef SEETAFACERECOGNIZER_DEPRECATED_NO_EXPORT
#  define SEETAFACERECOGNIZER_DEPRECATED_NO_EXPORT SEETAFACERECOGNIZER_NO_EXPORT SEETAFACERECOGNIZER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SEETAFACERECOGNIZER_NO_DEPRECATED
#    define SEETAFACERECOGNIZER_NO_DEPRECATED
#  endif
#endif

#endif /* SEETA_RECOGNIZER_API_H */
