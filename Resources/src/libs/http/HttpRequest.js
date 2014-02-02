/**
 * Created by chenyonghua on 13-11-8.
 */
HttpRequest = cc.Class.extend( {
    timeouts: 5,
    httpData: null,
    ctor: function()
    {
    },
    setData: function( httpData )
    {
        this.httpData = httpData;
    },
    setTimeOuts: function( seconds )
    {
        this.timeouts = seconds;
    },
    call: function()
    {
//        cc.log("this.timeouts:"+this.timeouts);
//        cc.log("this.httpData.uniqueId:"+this.httpData.uniqueId);
//        cc.log("this.httpData.path:"+this.httpData.path);
//        cc.log("this.httpData.params:"+JSON.stringify( this.httpData.params ));
        var httpRequest = new sf.JSHttpRequest();
        httpRequest.setTimeout( this.timeouts );
        httpRequest.setResponseCallback( this.onHttpDataResponse, this );
        httpRequest.call( this.httpData.path, "params=" + JSON.stringify( this.httpData.params ), this.httpData.uniqueId);
    },
    onHttpDataResponse: function( result, data )
    {
        if( result )
        {
            var remoteData;
            try
            {
                remoteData = JSON.parse( data );
            }
            catch( e )
            {
                cc.log( "JSON.decode 出错！" );
            }
            if( remoteData )
            {
                this.httpData.errorCode = remoteData.code;
                if( this.httpData.errorCode == 0 || this.httpData.errorCode == undefined)
                {
                    this.httpData.result = true;
                    this.httpData.remoteData = remoteData;
                }
                else
                {
                    this.httpData.remoteData = null;
                    this.httpData.errorMsg = remoteData.msg;
                }
            }
            else
            {
                this.httpData.result = false;
                this.httpData.errorMsg = "";
            }
        }
        else
        {
            this.httpData.result = false;
            this.httpData.errorMsg = "NetError";
        }
        if (this.httpData.callback != null)
        {
            this.httpData.callback.apply(this.httpData.target,[this.httpData]);
        }
        this.complete();
    },
    complete: function()
    {
        HttpManager.getInstance().callNextHttpRequest();
        this.httpData = null;
    }
} );