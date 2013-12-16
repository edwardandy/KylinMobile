/**
 * Created by chenyonghua on 13-11-6.
 */
UserModel = Model.extend({
    ctor:function()
    {
        this._super(UserModel.NAME);
    },
    onRegister:function()
    {
        this.dispatch(ContextEvent.START_UP,"UserModel",3,false,{"go":"yes"});
    }
});
UserModel.NAME = "UserModel";