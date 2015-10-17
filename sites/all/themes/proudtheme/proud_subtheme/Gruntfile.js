'use strict';

module.exports = function(grunt) {

  require('load-grunt-tasks')(grunt);

  var globalConfig = {
    theme_css: 'css',
    theme_scss: 'scss'
  };

  // Set up our sass files
  var sassFiles = {},
      fileNames = [
        'custom'
      ];

  // compile sass file paths
  for(var i = 0; i < fileNames.length; i++) {
    sassFiles['<%= globalConfig.theme_css %>/' + fileNames[i] + '.css'] = 'scss/' + fileNames[i] + '.<%= globalConfig.theme_scss %>';
  }

  grunt.initConfig({
    globalConfig: globalConfig,
    pkg: grunt.file.readJSON('package.json'),

    'node-inspector': {
      dev: {}
    },

    // Lib-sass
    sass: {
    	options: {
				includePaths: [
				  'bower_components/bootstrap-sass-official/assets/stylesheets',
				  'bower_components/bourbon/dist',
          'bower_components/proudcity-patterns/app'
				]
			},
      dev: {
        options: {
          outputStyle: 'nested', // expanded or nested or compact or compressed
          imagePath: '../images'
        },
        files: sassFiles
      }
    },

    watch: {
      grunt: { files: ['Gruntfile.js'] },

      sass: {
        files: ['scss/{,**/}*.s*ss'],
        tasks: ['sass:dev']
      },
			livereload: {
				files: ['**/*.html', '!node_modules/**', '!bower_components/**', 'js/**/*.js', 'css/**/*.css', 'images/**/*.{jpg,gif,svg,jpeg,png}'],
				options: {
					livereload: true
				}
			}
    }
  });

  grunt.registerTask('compile-sass', ['sass']);

  // Run watch at default settings
  grunt.registerTask('default', ['sass:dev', 'watch']);
}