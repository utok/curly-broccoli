'use strict';

module.exports = function(grunt) {

  require('load-grunt-tasks')(grunt);

  var globalConfig = {
    theme_css: 'css',
    theme_scss: 'scss',
    bootJsPath: 'bower_components/bootstrap-sass-official/assets/javascripts/bootstrap/'
  };

  // Set up our sass files
  var sassFiles = {},
      fileNames = [
        'custom-vendor',
        'custom'
      ];

  // compile sass file paths
  for(var i = 0; i < fileNames.length; i++) {
    sassFiles['<%= globalConfig.theme_css %>/' + fileNames[i] + '.css'] = 'scss/' + fileNames[i] + '.<%= globalConfig.theme_scss %>';
  }

  sassFiles['proud_subtheme/css/custom.css'] = 'proud_subtheme/scss/custom.scss';


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
    },

    uglify: {
      bootstrap: {
        options: {
          preserveComments: 'some',
          mangle: false
        },
        files: {
          'js/custom-bootstrap.min.js' : [
            '<%= globalConfig.bootJsPath %>transition.js',
            '<%= globalConfig.bootJsPath %>modal.js',
            '<%= globalConfig.bootJsPath %>affix.js',
            '<%= globalConfig.bootJsPath %>alert.js',
            '<%= globalConfig.bootJsPath %>button.js',
            'js/bootstrap/carousel-compatibility.js',
            '<%= globalConfig.bootJsPath %>collapse.js',
            '<%= globalConfig.bootJsPath %>dropdown.js',
            '<%= globalConfig.bootJsPath %>tooltip.js',
            '<%= globalConfig.bootJsPath %>popover.js',
            '<%= globalConfig.bootJsPath %>scrollspy.js',
            '<%= globalConfig.bootJsPath %>tab.js'
          ]
        }
      }
    },
  });

  grunt.registerTask('compile-sass', ['sass']);

  // Run watch with options
  grunt.registerTask('build', ['compile-sass', 'uglify']);

  // Run watch at default settings
  grunt.registerTask('default', ['sass:dev', 'watch']);
}