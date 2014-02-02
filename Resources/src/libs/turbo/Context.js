/**
 * Created by chenyonghua on 13-11-5.
 */
Context = cc.Class.extend( {
    signalBus: null,
    controllerMap: null,
    modelMap: null,
    serviceMap: null,
    ctor: function()
    {
        if( Context.INSTANCE )
        {
            throw(new Error( "Context already exists" ));
        }

        this.controllerMap = {};
        this.modelMap = {};
        this.serviceMap = {};
        this.signalBus = new SignalBus();
    },
    getSignalBus: function()
    {
        return this.signalBus;
    },
    // controller
    registerController: function( controller )
    {
        if( typeof(controller.getName()) != "string" || !controller.getName() )
        {
            throw new Error( "the controller's name " + controller.getName() + " is not legal. " );
            return;
        }
        if( this.controllerMap[controller] != null )
        {
            throw new Error( "the controller named " + controller.getName() + " already exist. " );
            return;
        }
        if( this.controllerMap[controller.getName()] == null )
        {
            this.controllerMap[controller.getName()] = controller;
            controller.onRegister();
        }
    },
    retrieveController: function( controllerName )
    {
        if( this.controllerMap[controllerName] == null )
        {
            throw new Error( "the controller named " + controllerName + " doesn't exist. " );
            return null;
        }
        return this.controllerMap[controllerName];
    },
    hasController: function( controllerName )
    {
        return this.controllerMap[controllerName] != null;
    },
    unRegisterController: function( controllerName )
    {
        if( this.controllerMap[controllerName] == null )
        {
            throw new Error( "the controller named " + controllerName + " doesn't exist. " );
            return null;
        }
        this.controllerMap[controllerName].onRemove();
        delete this.controllerMap[controllerName];
    },

    //model
    registerModel: function( model )
    {
        if( typeof(model.getName()) != "string" || !model.getName() )
        {
            throw new Error( "the model's name " + model.getName() + " is not legal. " );
            return;
        }
        if( this.modelMap[model.getName()] != null )
        {
            throw new Error( "the model named " + model.getName() + " already exist. " );
            return;
        }
        if( this.modelMap[model.getName()] == null )
        {
            this.modelMap[model.getName()] = model;
            model.onRegister();
        }
    },
    retrieveModel: function( modelName )
    {
        if( this.modelMap[modelName] == null )
        {
            throw new Error( "the model named " + modelName + " doesn't exist. " );
            return null;
        }
        return this.modelMap[modelName];
    },
    hasModel: function( modelName )
    {
        return this.modelMap[modelName] != null;
    },
    unRegisterModel: function( modelName )
    {
        if( this.modelMap[modelName] == null )
        {
            throw new Error( "the model named " + modelName + " doesn't exist. " );
            return null;
        }
        this.modelMap[modelName].onRemove();
        delete this.modelMap[modelName];
    },

    //service
    registerService: function( service )
    {
        if( typeof(service.getName()) != "string" || !service.getName() )
        {
            throw new Error( "the service's name " + service.getName() + " is not legal. " );
            return;
        }
        if( this.serviceMap[service.getName()] != null )
        {
            throw new Error( "the service named " + service.getName() + " already exist. " );
            return;
        }
        if( this.serviceMap[service.getName()] == null )
        {
            this.serviceMap[service.getName()] = service;
            service.onRegister();
        }
    },
    retrieveService: function( serviceName )
    {
        if( this.serviceMap[serviceName] == null )
        {
            throw new Error( "the service named " + serviceName + " doesn't exist. " );
            return null;
        }
        return this.serviceMap[serviceName];
    },
    hasService: function( serviceName )
    {
        return this.serviceMap[serviceName] != null;
    },
    unRegisterService: function( serviceName )
    {
        if( this.serviceMap[serviceName] == null )
        {
            throw new Error( "the service named " + serviceName + " doesn't exist. " );
            return null;
        }
        this.serviceMap[serviceName].onRemove();
        delete this.serviceMap[serviceName];
    },
    dispatch: function( type, params )
    {
        var paramsArr = Array.prototype.slice.call( arguments );
        //remove the type
        paramsArr.shift();
        this.signalBus.dispatch( type, paramsArr );
    }
} );
Context.INSTANCE = null;
Context.getInstance = function()
{
    if( Context.INSTANCE == null )
    {
        Context.INSTANCE = new Context();
    }
    return Context.INSTANCE;
}