#ifndef MOCKHTTPREQUESTMANAGER_H
#define MOCKHTTPREQUESTMANAGER_H

#include <gmock/gmock.h>
#include "networking/httprequestmanager.h"

class MockHttpRequestManager: public HttpRequestManager
{
public:
    MOCK_METHOD(void, request, (HttpRequest httpRequest, OnFinished onResponse), (override));
};
#endif // MOCKHTTPREQUESTMANAGER_H
