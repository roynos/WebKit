/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NavigatorIsLoggedIn.h"

#include "JSDOMPromiseDeferred.h"
#include "Navigator.h"

namespace WebCore {

NavigatorIsLoggedIn* NavigatorIsLoggedIn::from(Navigator& navigator)
{
    auto* supplement = static_cast<NavigatorIsLoggedIn*>(Supplement<Navigator>::from(&navigator, supplementName()));
    if (!supplement) {
        auto newSupplement = makeUnique<NavigatorIsLoggedIn>(navigator);
        supplement = newSupplement.get();
        provideTo(&navigator, supplementName(), WTFMove(newSupplement));
    }
    return supplement;
}

ASCIILiteral NavigatorIsLoggedIn::supplementName()
{
    return "NavigatorIsLoggedIn"_s;
}

void NavigatorIsLoggedIn::setLoggedIn(Navigator& navigator, Ref<DeferredPromise>&& promise)
{
    NavigatorIsLoggedIn::from(navigator)->setLoggedIn(WTFMove(promise));
}

void NavigatorIsLoggedIn::setLoggedOut(Navigator& navigator, Ref<DeferredPromise>&& promise)
{
    NavigatorIsLoggedIn::from(navigator)->setLoggedOut(WTFMove(promise));
}

void NavigatorIsLoggedIn::isLoggedIn(Navigator& navigator, Ref<DeferredPromise>&& promise)
{
    NavigatorIsLoggedIn::from(navigator)->isLoggedIn(WTFMove(promise));
}

void NavigatorIsLoggedIn::setLoggedIn(Ref<DeferredPromise>&& promise)
{
    if (m_navigator.cookieEnabled())
        promise->resolve();
    else
        promise->reject();
}

void NavigatorIsLoggedIn::setLoggedOut(Ref<DeferredPromise>&& promise)
{
    promise->resolve();
}

void NavigatorIsLoggedIn::isLoggedIn(Ref<DeferredPromise>&& promise)
{
    if (m_navigator.cookieEnabled())
        promise->resolve<IDLBoolean>(true);
    else
        promise->resolve<IDLBoolean>(false);
}

} // namespace WebCore
