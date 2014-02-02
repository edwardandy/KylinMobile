/**
 * Created by chenyonghua on 13-11-6.
 */
Service = Actor.extend({
    ctor:function(serviceName)
    {
        this.serviceName = serviceName || this.constructor.NAME;
    },
    dispatch: function( type, params )
    {
        var paramsArr = Array.prototype.slice.call( arguments );
        //remove the type
        paramsArr.shift();
        this.getSignalBus().dispatch( type, paramsArr );
    }
});

Service.NAME = "Service";

Service.prototype.getName = function()
{
    return this.serviceName;
};

Service.prototype.onRegister = function()
{
    return;
};

Service.prototype.onRemove = function()
{
    return;
};

Service.prototype.serviceName = null;