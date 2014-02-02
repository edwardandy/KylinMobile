/**
 * Created by chenyonghua on 13-11-5.
 */
var context = Context.getInstance();
context.registerController(new GameController(cc.Scene.create()));
context.registerModel(new UserModel());
context.registerService(new GameStartService());

//context.dispatch("abc",{"go":"yes"});
context.dispatch(ContextEvent.START_UP,"Context",1,true,{"go":"yes"});