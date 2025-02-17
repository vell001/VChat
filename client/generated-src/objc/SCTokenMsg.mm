// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#import "SCTokenMsg.h"


@implementation SCTokenMsg

- (nonnull instancetype)initWithToken:(nonnull NSString *)token
                    expirationTimeSec:(int32_t)expirationTimeSec
                             username:(nonnull NSString *)username
{
    if (self = [super init]) {
        _token = [token copy];
        _expirationTimeSec = expirationTimeSec;
        _username = [username copy];
    }
    return self;
}

+ (nonnull instancetype)tokenMsgWithToken:(nonnull NSString *)token
                        expirationTimeSec:(int32_t)expirationTimeSec
                                 username:(nonnull NSString *)username
{
    return [(SCTokenMsg*)[self alloc] initWithToken:token
                                  expirationTimeSec:expirationTimeSec
                                           username:username];
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<%@ %p token:%@ expirationTimeSec:%@ username:%@>", self.class, (void *)self, self.token, @(self.expirationTimeSec), self.username];
}

@end
