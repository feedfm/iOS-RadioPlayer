//
//  FMLog.h
//  sdktest
//
//  Created by James Anthony on 10/1/12.
//  Copyright (c) 2012-2016 Feed Media Inc. All rights reserved.
//
#ifdef __cplusplus
extern "C"{
#endif

typedef enum FMLogLevel : NSInteger {
    FMLogLevelNone = 0,
    FMLogLevelError = 1,
    FMLogLevelWarn = 2,
    FMLogLevelDebug = 3
} FMLogLevel;

void FMLogSetLevel(FMLogLevel level);
void _FMLog(NSInteger level, NSString *format, ...);

#ifndef FMLog
#define FMLog(level,fmt,...) _FMLog(level, (@"%s (%d): " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#endif

#ifndef FMLogDebug
#define FMLogDebug(...) FMLog(FMLogLevelDebug,__VA_ARGS__)
#endif

#ifndef FMLogWarn
#define FMLogWarn(...) FMLog(FMLogLevelWarn,__VA_ARGS__)
#endif

#ifndef FMLogError
#define FMLogError(...) FMLog(FMLogLevelError,__VA_ARGS__)
#endif

#ifdef __cplusplus
}
#endif
