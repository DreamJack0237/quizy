
const nodeExternals = require("webpack-node-externals");

const path = require('path');
const changeBuildDirectory = require('craco-change-build-directory');

const newBuildPath = path.resolve('build/ui/ressources');
module.exports = {
    Plugin:
        [
            {
                plugin: changeBuildDirectory,
                options: {
                    newPath: 'build/ui/ressources',
                },
            },
        ],
    webpack: {
        configure: {
            target: ['electron-renderer'],
            externals: [
                nodeExternals({
                    allowlist: [/webpack(\/.*)?/, "electron-devtools ['web', 'es5'],-installer"],
                }),
            ],// or send to an analytics endpoint. Learn more: https ['web', 'es5'],://bit.ly/CRA-vitals

        },
    },
};