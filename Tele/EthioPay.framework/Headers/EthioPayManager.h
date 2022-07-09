//
//  EthioPayManager.h
//  EthioPay
//
//  Created by xiaoxidong on 2021/6/8.
//

#import <Foundation/Foundation.h>
#import "NetWorkManager.h"
#import "EthioPayViewController.h"
#import "RSA.h"
#import "MBProgressHUD.h"


NS_ASSUME_NONNULL_BEGIN

@protocol EthioPayManagerDelegate <NSObject>


/**
 When the payment is completed, the SDK calls back to this interface to inform the APP of the payment result.
 @param code  Status Code   1:
 @param msg  Status Code Description
 @param data Contains two parameters: 1. outTradeNo  Merchant website order number, which is customized by the merchant.      2.tradeNo  Transaction sequence number in the Mobile Money payment system. The value contains a maximum of 64 bits.
 */
- (void)getPaymentResultCallBackWithCode:(NSString *)code message:(NSString *)msg paymentData:(NSDictionary *)data;

/**
  Close the payment page and stop the payment request (before the customer confirm the payment, the merchant can call this API to stop the payment)
 */
- (void)stopPayment;


@end


@interface EthioPayManager : NSObject<EthioPayViewControllerDelegate,MBProgressHUDDelegate>
{
}
@property(nonatomic,retain)NSString *appID;
@property(nonatomic,retain)NSString *appKey;
@property(nonatomic,retain)NSString *publicKey;
@property(nonatomic,retain)NSString *serviceUrl;

@property(nonatomic,retain)EthioPayViewController *ethioPayViewVC;

@property(nonatomic,assign)id<EthioPayManagerDelegate> delegate;
@property(nonatomic,assign)BOOL isProductionEnvironment;

/**
 Single case
 */
+(instancetype)sharedInstance;

/**
  Display the payment page in the App and guide the user to complete the payment step by step
 @param appID  AppId provided by the platform
 @param appkey  appkey provided by the platform
 @param publicKey  publicKey provided by the platform
 @param returnUrl  H5 URL for redirecting to the e-mall page after the app payment is complete (successful or failed).
 @param notifyUrl  Payment result notification URL. HTTP/HTTPS path for the Mobile Money APPServer to proactively notify the merchant server of the payment result. If this parameter is left blank, no notification is sent.
 @param subject  Item title, etc. Note: Special characters such as /, =, & are not allowed.
 @param outTradeNo  Merchant website order number, which is customized by the merchant and must be unique in the merchant system. Only digits, letters, and underscores are supported.
 @param timeoutExpress  Indicates the latest payment time allowed for an order. The transaction will be closed if the order expires, in minutes.
 @param totalAmount  Total order amount, in ETB. The value ranges from 0.01 to 100000000.00 and is accurate to two decimal places.
 @param shortCode  Merchant ShortCode
 @param receiveName  Recipient Name
 */
- (void)startPaymentWithAppid:(NSString *)appID appKey:(NSString *)appkey publicKey:(NSString *)publicKey returnUrl:(NSString *)returnUrl notifyUrl:(NSString *)notifyUrl subject:(NSString *)subject outTradeNo:(NSString *)outTradeNo timeoutExpress:(NSString *)timeoutExpress totalAmount:(NSString *)totalAmount shortCode:(NSString *)shortCode receiveName:(NSString *)receiveName callback:(void (^)(NSDictionary *result))callback;


@end

NS_ASSUME_NONNULL_END
