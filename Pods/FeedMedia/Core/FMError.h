//
//  FMError.h
//  sdktest
//
//  Created by James Anthony on 3/12/13.
//  Copyright (c) 2013-2016 Feed Media, Inc. All rights reserved.
//

extern NSString * const FMAPIErrorDomain;

/**
 *  @enum FMErrorCode
 *  Represents error codes
 *  @const FMErrorCodeRequestFailed Request failed because of connection error
 *  @const FMErrorCodeUnexpectedReturnType Returned JSON has unexpected structure
 *  @const FMErrorCodeInvalidCredentials Authentification is required, but no authentification information available.
 *  @const FMErrorCodeInvalidSkip   Invalid Skip Request was sent. It might happen if skip is requested while no song is currently playing
 */
typedef enum FMErrorCode : NSInteger {
    FMErrorCodeRequestFailed = -4,
    FMErrorCodeUnexpectedReturnType = -1,
    FMErrorCodeInvalidCredentials = 5,
    FMErrorCodeAccessForbidden = 6,
    FMErrorCodeSkipLimitExceeded = 7,
    FMErrorCodeNoAvailableMusic = 9,
    FMErrorCodeInvalidSkip = 12,
    FMErrorCodeInvalidParameter = 15,
    FMErrorCodeMissingParameter = 16,
    FMErrorCodeNoSuchResource = 17,
    FMErrorCodeInternal = 18,
    FMErrorCodeInvalidRegion = 19
} FMErrorCode;
