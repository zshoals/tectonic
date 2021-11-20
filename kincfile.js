let project = new Project('Tectonic');

project.addFile('Sources/**');
project.setDebugDir('Deployment');

resolve(project);
