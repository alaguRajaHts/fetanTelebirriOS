//
//  ViewController.m
//  Tele
//
//  Created by HTS-MAC on 07/07/22.
//

#import "ViewController.h"
#import "EthioPay.framework/Headers/EthioPayManager.h"
#import "EthioPay.framework/Headers/EthioPayViewController.h"
#import "EthioPay.framework/Headers/NetWorkManager.h"
#import "EthioPay.framework/Headers/EthioPayViewController.h"

@interface ViewController ()<EthioPayManagerDelegate,EthioPayViewControllerDelegate>
{
    EthioPayManager* telebirr;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    telebirr = [EthioPayManager sharedInstance];
    telebirr.appID = @"292d03e2b4814010bb75c1809e3dc893";
    telebirr.appKey = @"06063d2649ea44b6b2f35a7c8230d3ae";
    telebirr.publicKey = @"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnuUckmy5nWbH7haQmx6uizxB1bJput/v/lIZoWPcAQEeNDwMGhq/r+PsjDna3mncNzRKLUIZ3lcU5V6CCbjXNKR+xcnsg8dwHYaPj+qG3ASVZQRoRvP7l+JgKCREYCsP42wwTSIr95YK8Zu94Tsh7f0/Q9HH9oYZFIEOiT5qm9rsfZ7XaMCa/BF9xPZEC8brPWXw8yRuUBL8SEmddhAGpdi5rdBugVeP1I38Z6mbYA1besj42ntpw+eCqek8NiO+TFMD8TAz38W3IfVyU2bdoROCm21uWGQ4dN4WFkVKxbJwQr6rl2IxHSjaW/p2v3RsUikQ8XREvvCJvO+4hakk+QIDAQAB";
    telebirr.serviceUrl = @"http://196.188.120.3:11443/service-openup";
//    //@"http://196.188.120.3:11443/ammapi/payment/service-openup";
    [self initalSetup];
}

-(void) initalSetup {
    [self.view setBackgroundColor:UIColor.greenColor];
    
    UIButton *button= [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
    [button setFrame:CGRectMake(self.view.frame.size.width/2-100, self.view.frame.size.height/2-40, 200, 40)];
    [button setTitle:@"Click" forState:UIControlStateNormal];
    [button setExclusiveTouch:YES];
    [button setBackgroundColor:UIColor.blackColor];
    [self.view addSubview:button];
    
    //SETUP Telebirr Object
    telebirr.delegate = self;
    telebirr.delegate = self;
}

//MARK: Present Payment ViewController
-(void) buttonClicked:(UIButton*)sender {
    NSString *outTradeNo = [self getRandomPINString:16]; //@"201219350059612378211"
    NSLog(@"%@",outTradeNo);
    
//    telebirr
    [telebirr startPaymentWithAppid:@"292d03e2b4814010bb75c1809e3dc893" appKey:@"06063d2649ea44b6b2f35a7c8230d3ae" publicKey:@"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAnuUckmy5nWbH7haQmx6uizxB1bJput/v/lIZoWPcAQEeNDwMGhq/r+PsjDna3mncNzRKLUIZ3lcU5V6CCbjXNKR+xcnsg8dwHYaPj+qG3ASVZQRoRvP7l+JgKCREYCsP42wwTSIr95YK8Zu94Tsh7f0/Q9HH9oYZFIEOiT5qm9rsfZ7XaMCa/BF9xPZEC8brPWXw8yRuUBL8SEmddhAGpdi5rdBugVeP1I38Z6mbYA1besj42ntpw+eCqek8NiO+TFMD8TAz38W3IfVyU2bdoROCm21uWGQ4dN4WFkVKxbJwQr6rl2IxHSjaW/p2v3RsUikQ8XREvvCJvO+4hakk+QIDAQAB" returnUrl:@"http://services.hitasoft.in/dev/telebirr_resp.php" notifyUrl:@"http://services.hitasoft.in/dev/fetanup/products/telebirr_notify?custom=3&action_type=banner" subject:@"Buy cinema ticket" outTradeNo:outTradeNo timeoutExpress:@"10" totalAmount:@"9.23" shortCode: @"220118" receiveName:@"Fetan technology" callback:^(NSDictionary* result) {
        NSLog(@"!!!%@",result);
    }];
 }

//MARK: GetRandom String numbers for outTradeNo
-(NSString *)getRandomPINString:(NSInteger)length
{
    NSMutableString *returnString = [NSMutableString stringWithCapacity:length];
    NSString *numbers = @"0123456789";

    // First number cannot be 0
    [returnString appendFormat:@"%C", [numbers characterAtIndex:(arc4random() % ([numbers length]-1))+1]];
    for (int i = 1; i < length; i++)
    {
        [returnString appendFormat:@"%C", [numbers characterAtIndex:arc4random() % [numbers length]]];
    }
    NSLog(@"RandomString for outTradeNo = %@",returnString);
    return returnString;
}

- (void)dissmissVC{
    [[telebirr ethioPayViewVC] dismissViewControllerAnimated:true completion:nil];
}



//MARK: EthioPay Delegate Funcions

- (void)getPaymentResultCallBackWithCode:(NSString *)code message:(NSString *)msg paymentData:(NSDictionary *)data{
    NSLog(@"!!CODE= %@, MESSAGE= %@, PaymentData = %@",code,msg,data);
}
- (void)stopPayment{
    NSLog(@"!!Payment Stoped");

}
- (void)cancelPayMentAction{
    NSLog(@"CancelAction");

}
- (void)completePayMentAction:(NSDictionary *)dic{
    NSLog(@"RESLT%@",dic);

}

//MARK: Present Payment ViewController
-(void) showAlert:(NSString*)Text {
    UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"My Alert"
                                   message:Text
                                   preferredStyle:UIAlertControllerStyleAlert];

    UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault
       handler:^(UIAlertAction * action) {}];

    [alert addAction:defaultAction];
    [self presentViewController:alert animated:YES completion:nil];
    
}
@end
