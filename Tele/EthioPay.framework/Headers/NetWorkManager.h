//
//  NetWorkManager.h
//  Afnetworking repackaging
//
//  Created by xiaoxd on 16/5/20.
//  Copyright © 2021年 xiaoxd. All rights reserved.
//

#import "AFNetworking.h"
#define BaseURL @"http://196.188.120.3:11443/ammapi/payment/service-openup"
//#define BaseURL @"http://amm.easier.cn/service-openup"

/**Enumeration that defines the type of request*/

typedef NS_ENUM(NSUInteger,HttpRequestType)
{
    
    HttpRequestTypeGet = 0,
    HttpRequestTypePost
    
};


/**Define the successful block of the request*/
typedef void(^requestSuccess)( NSDictionary * object);

/**Define the block where the request failed*/
typedef void(^requestFailure)( NSError *error);

/**Define upload progress block*/
typedef void(^uploadProgress)(float progress);

/**Define download progress block*/
typedef void(^downloadProgress)(float progress);


@interface NetWorkManager : AFHTTPSessionManager

//@property(nonnull,retain)NSString *baseURL;

/**
 *  Single case method
 *
 *  @return Instance object
 */
+(instancetype)shareManager;

/**
 *  Instance method of network request
 *
 *  @param type         get / post
 *  @param urlString    Requested address
 *  @param paraments    Requested parameters
 *  @param successBlock Request successful callback
 *  @param failureBlock Callback for request failure
 *  @param progress speed of progress
 */
-(void)requestWithType:(HttpRequestType)type withUrlString:(NSString *)urlString withParaments:(id)paraments withSuccessBlock:( requestSuccess)successBlock withFailureBlock:( requestFailure)failureBlock progress:(downloadProgress)progress;

/**
 *  Upload pictures
 *
 *  @param operations   Reserved parameters for uploading pictures --- can be removed as the case may be
 *  @param imageArray   Uploaded image array
 *  @parm width      The width of the image to be compressed
 *  @param urlString    Upload URL
 *  @param successBlock Callback for successful upload
 *  @param failureBlock Callback for upload failure
 *  @param progress     Upload progress
 */

+(void)uploadImageWithOperations:(NSDictionary *)operations withImageArray:(NSArray *)imageArray withtargetWidth:(CGFloat )width withUrlString:(NSString *)urlString withSuccessBlock:(requestSuccess)successBlock withFailurBlock:(requestFailure)failureBlock withUpLoadProgress:(uploadProgress)progress;


/**
*Video upload
*
*@ param operations upload video reservation parameters --- can be removed as the case may be
*@ param videopath local sand river path to upload video
*@ param urlstring upload URL
*@ param successblock successful callback
*@ param failureblock failed callback
*@ param progress upload progress
*/
+(void)uploadVideoWithOperaitons:(NSDictionary *)operations withVideoPath:(NSString *)videoPath withUrlString:(NSString *)urlString withSuccessBlock:(requestSuccess)successBlock withFailureBlock:(requestFailure)failureBlock withUploadProgress:(uploadProgress)progress;


/**
*File download
*
*Download the reserved parameters from @ param operations file --- it can be removed according to the specific situation
*@ param savepath download file save path
*@ param urlstring URL of the request
*@ param successblock successful callback for downloading files
*@ param failureblock callback for file download failure
*@ param progress Download File progress display
*/


+(void)downLoadFileWithOperations:(NSDictionary *)operations withSavaPath:(NSString *)savePath withUrlString:(NSString *)urlString withSuccessBlock:(requestSuccess)successBlock withFailureBlock:(requestFailure)failureBlock withDownLoadProgress:(downloadProgress)progress;

/**
* cancel all network requests.
*/


+(void)cancelAllRequest;
/**
*URL to cancel the specified request
*
*@ param requesttype the request type of the request
*@ param string URL of the request
*/

+(void)cancelHttpRequestWithRequestType:(NSString *)requestType requestUrlString:(NSString *)string;




@end
