/**
 * @file utils.h
 * @author hbuyse
 * @date 14/02/2018
 *
 * @brief  Common utils macro
 */

#ifndef __NETLOGGINGD_UTILS_H__
#define __NETLOGGINGD_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>   // calloc, malloc, free, realloc
#include <string.h>   // strdup
#include <syslog.h>

/**
 * @brief      Get the number of elements of the given array
 *
 * @param      x     Pointer to the array
 *
 * @return     The number of elements of the given array
 */
#define NELEMS(x) sizeof((x)) / sizeof((x)[0])

/**
 * @brief Macro that logs an error trace into the syslog
 */
#ifndef NDEBUG
#define TRACE_ERROR(fmt, ...)                                                                            \
  do                                                                                                     \
  {                                                                                                      \
    syslog(LOG_ERR, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);        \
    fprintf(stderr, "\e[31m[ERROR][%s:%d][%s] - " fmt "\e[0m\n", basename(__FILE__), __LINE__, __func__, \
            ##__VA_ARGS__);                                                                              \
  } while (0)
#else
#  define TRACE_ERROR(fmt, ...)                                                                       \
    do                                                                                               \
    {                                                                                                \
      syslog(LOG_ERR, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif

/**
 * @brief Macro that logs an warning trace into the syslog
 */
#ifndef NDEBUG
#define TRACE_WARNING(fmt, ...)                                                                            \
  do                                                                                                       \
  {                                                                                                        \
    syslog(LOG_WARNING, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);      \
    fprintf(stderr, "\e[33m[WARNING][%s:%d][%s] - " fmt "\e[0m\n", basename(__FILE__), __LINE__, __func__, \
            ##__VA_ARGS__);                                                                                \
  } while (0)
#else
#  define TRACE_WARNING(fmt, ...)                                                                       \
    do                                                                                               \
    {                                                                                                \
      syslog(LOG_WARNING, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif

/**
 * @brief Macro that logs an info trace into the syslog
 */
#ifndef NDEBUG
#  define TRACE_INFO(fmt, ...)                                                                                      \
    do                                                                                                              \
    {                                                                                                               \
      syslog(LOG_INFO, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);                \
      fprintf(stdout, "[INFO][%s:%d][%s] - " fmt "\e[0m\n", basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#else
#  define TRACE_INFO(fmt, ...)                                                                       \
    do                                                                                               \
    {                                                                                                \
      syslog(LOG_INFO, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif

/**
 * @brief Macro that logs a debug trace into the syslog
 */
#ifndef NDEBUG
#  define TRACE_DEBUG(fmt, ...)                                                                            \
    do                                                                                                     \
    {                                                                                                      \
      syslog(LOG_DEBUG, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__);      \
      fprintf(stdout, "\e[37m[DEBUG][%s:%d][%s] - " fmt "\e[0m\n", basename(__FILE__), __LINE__, __func__, \
              ##__VA_ARGS__);                                                                              \
    } while (0)
#else
#  define TRACE_DEBUG(fmt, ...)                                                                       \
    do                                                                                                \
    {                                                                                                 \
      syslog(LOG_DEBUG, "[%s:%d][%s] - " fmt, basename(__FILE__), __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)
#endif

/**
 * @def        sm_free
 * @brief      Trace the call of a free function and safely free the pointer
 *
 * @param      x     Pointer to free
 */
#define sm_free(x)                    \
  do                                  \
  {                                   \
    if ((x))                          \
    {                                 \
      TRACE_DEBUG("Free of %p", (x)); \
      free((x));                      \
      (x) = NULL;                     \
    }                                 \
  } while (0)

/**
 * @def        sm_calloc
 * @brief      Trace the call of a calloc function
 *
 * @param      __nmemb   Number of elements to allocate
 * @param      __size    Size of a element
 */
#define sm_calloc(__nmemb, __size)                                 \
  ({                                                               \
    void* __ret;                                                   \
    __ret = calloc((__nmemb), (__size));                           \
    TRACE_DEBUG("Callocation of %p (size: %zu)", __ret, (__size)); \
    __ret;                                                         \
  })

/**
 * @def        sm_malloc
 * @brief      Trace the call of a malloc function
 *
 * @param      __size    Size to allocate
 */
#define sm_malloc(__size)                                          \
  ({                                                               \
    void* __ret;                                                   \
    __ret = malloc((__size));                                      \
    TRACE_DEBUG("Mallocation of %p (size: %zu)", __ret, (__size)); \
    __ret;                                                         \
  })

/**
 * @def        sm_realloc
 * @brief      Trace the call of a malloc function
 *
 * @param      __ptr     Pointer to realloc
 * @param      __size    Size to allocate
 */
#define sm_realloc(__ptr, __size)                                                  \
  ({                                                                               \
    void* __ret;                                                                   \
    __ret = realloc((__ptr), (__size));                                            \
    TRACE_DEBUG("Reallocation of %p to %p (size: %zu)", (__ptr), __ret, (__size)); \
    __ret;                                                                         \
  })

/**
 * @def        sm_strdup
 * @brief      Trace the call of a strdup function
 *
 * @param      __string  The string
 */
#define sm_strdup(__string)                                        \
  ({                                                               \
    char* __ret;                                                   \
    __ret = strdup(__string);                                      \
    TRACE_DEBUG("Strdup of %p (size: %zu)", __ret, strlen(__ret)); \
    __ret;                                                         \
  })

/**
 * @def        sm_return_if_fail
 * @brief      Check the validity of a condition
 *
 * @param[in]  cond  The condition to check
 *
 * @return     Does not return value but this macro allow the program to exit the current function where it is called
 */
#define sm_return_if_fail(cond)                    \
  do                                               \
  {                                                \
    if (!(cond))                                   \
    {                                              \
      TRACE_ERROR("Condition failed '%s'", #cond); \
      return;                                      \
    }                                              \
  } while (0)

/**
 * @def        sm_return_if_fail_errno
 * @brief      Check the validity of a condition and trace with errno
 *
 * @param[in]  cond  The condition to check
 *
 * @return     Does not return value but this macro allow the program to exit the current function where it is called
 */
#define sm_return_if_fail_errno(cond)                   \
  do                                                    \
  {                                                     \
    if (!(cond))                                        \
    {                                                   \
      TRACE_ERROR("Condition failed '%s' - %m", #cond); \
      return;                                           \
    }                                                   \
  } while (0)

/**
 * @def        sm_return_val_if_fail
 * @brief      Check the validity of a condition
 *
 * @param[in]  cond  The condition to check
 * @param[in]  val   The value to return
 *
 * @return     Return the value but this macro allow the program to exit the current function where it is called
 */
#define sm_return_val_if_fail(cond, val)           \
  do                                               \
  {                                                \
    if (!(cond))                                   \
    {                                              \
      TRACE_ERROR("Condition failed '%s'", #cond); \
      return val;                                  \
    }                                              \
  } while (0)

/**
 * @def        sm_return_val_if_fail_errno
 * @brief      Check the validity of a condition and trace with errno
 *
 * @param[in]  cond  The condition to check
 * @param[in]  val   The value to return
 *
 * @return     Return the value but this macro allow the program to exit the current function where it is called
 */
#define sm_return_val_if_fail_errno(cond, val)          \
  do                                                    \
  {                                                     \
    if (!(cond))                                        \
    {                                                   \
      TRACE_ERROR("Condition failed '%s' - %m", #cond); \
      return val;                                       \
    }                                                   \
  } while (0)

#ifdef __cplusplus
}
#endif

#endif   // __NETLOGGINGD_UTILS_H__
