let project = new Project('Tectonic');

project.addFile('Sources/**');
project.addFiles('Sources/shaders/**');
project.addFiles('Sources/assets/**');
project.addIncludeDir('Sources');
project.setDebugDir('Deployment');
project.addDefine('TEC_LOG_LOGGING_ENABLED=1');

resolve(project);

//Possible flags are:
//TEC_DISABLE_UNFORCED_ASSERTS to disable any non-mandatory assertions
//TEC_DISABLE_TESTS to disable the runtime tests launched before main