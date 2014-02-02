/**
 * Created by chenyonghua on 13-11-6.
 */
Actor = cc.Class.extend( {
    signalBus:null,
    context:null,
    ctor: function()
    {
        this.signalBus = null;
        this.context   = null;
    },
    getContext:function()
    {
        return Context.getInstance();
    },
    getSignalBus:function()
    {
        return this.getContext().getSignalBus();
    }
});