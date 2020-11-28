
#ifndef SEETA_DETECTOR_API_H
#define SEETA_DETECTOR_API_H

#ifdef SEETAFACEDETECTOR_STATIC_DEFINE
#  define SEETA_DETECTOR_API
#  define SEETAFACEDETECTOR_NO_EXPORT
#else
#  ifndef SEETA_DETECTOR_API
#    ifdef SeetaFaceDetector_EXPORTS
        /* We are building this library */
#      define SEETA_DETECTOR_API __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SEETA_DETECTOR_API __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef SEETAFACEDETECTOR_NO_EXPORT
#    define SEETAFACEDETECTOR_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef SEETAFACEDETECTOR_DEPRECATED
#  define SEETAFACEDETECTOR_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SEETAFACEDETECTOR_DEPRECATED_EXPORT
#  define SEETAFACEDETECTOR_DEPRECATED_EXPORT SEETA_DETECTOR_API SEETAFACEDETECTOR_DEPRECATED
#endif

#ifndef SEETAFACEDETECTOR_DEPRECATED_NO_EXPORT
#  define SEETAFACEDETECTOR_DEPRECATED_NO_EXPORT SEETAFACEDETECTOR_NO_EXPORT SEETAFACEDETECTOR_DEPRECATED
#endif

#define DEFINE_NO_DEPRECATED 0
#if DEFINE_NO_DEPRECATED
# define SEETAFACEDETECTOR_NO_DEPRECATED
#endif

#endif
