let project = new Project('Tectonic');

project.addFile('Sources/**');
project.setDebugDir('Deployment');
project.addDefine('TEC_LOG_LOGGING_ENABLED=1');

resolve(project);
