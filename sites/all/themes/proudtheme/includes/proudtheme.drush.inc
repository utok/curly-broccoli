<?php
/**
 * @file Stolen from zurb_foundation
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function proudtheme_drush_command() {
  $items = array();

  $items['proud-sub-theme'] = array(
    'description' => 'Create a ProudTheme sub-theme',
    'arguments' => array(
      'name'         => 'Your sub-theme name.',
      'machine_name' => 'A machine-readable name for your theme, optional only  [a-z, 0-9] ',
    ),
    'options' => array(
      'description'  => 'Your sub-theme description.',
      'machine-name' => '[a-z, 0-9] A machine-readable name for your theme.',
      //'name'         => 'A name for your theme.',
      //'without-rtl'  => 'Remove all RTL stylesheets.',
    ),
    'examples' => array(
      'drush proud-sub-theme "custom theme name"' => 'Create a sub-theme with the default options.',
      'drush proud-sub-theme "foo bar" "foo_bar"  --description="My supersweet awesome theme"' => 'Create a sub-theme with additional options.',
    ),
  );

  return $items;
}

/**
 * Create a ProudTheme sub-theme.
 */
function drush_proudtheme_proud_sub_theme($name = NULL, $machine_name = NULL, $description = NULL) {
  if (empty($name)) {
    drush_set_error(dt("Please provide a name for the sub-theme.\nUSAGE:\tdrush proud-sub-theme [name] [machine_name !OPTIONAL] [description !OPTIONAL]\n"));
    return;
  }
  //Filter everything but letters, numbers, underscores, and hyphens
  $machine_name = !empty($machine_name) ? preg_replace('/[^a-z0-9_-]+/', '', strtolower($machine_name)) : preg_replace('/[^a-z0-9_-]+/', '', strtolower($name));
  // Eliminate hyphens
  $machine_name = str_replace('-', '_', $machine_name);

  // Find theme paths.
  $proud_path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('theme', 'proudtheme');
  $subtheme_path = dirname($proud_path) . '/' . $machine_name;

  // Make a fresh copy of the subtheme.
  $s = drush_copy_dir("$proud_path/proud_subtheme/", $subtheme_path);
  if (empty($s)) {
    return;
  }

  // Rename files and fill in the theme machine name
  drush_op('rename', "$subtheme_path/proud_subtheme.info.txt", "$subtheme_path/$machine_name.info");
  drush_op('rename', "$subtheme_path/js/scripts.js", "$subtheme_path/js/$machine_name.js");
  // Update the .info file
  drush_op('proudtheme_file_str_replace', "$subtheme_path/$machine_name.info", 'ProudTheme Subtheme', "$name");
  // Change the name of the theme
  if (!empty($description)) {
    drush_op('proudtheme_file_str_replace', "$subtheme_path/$machine_name.info", 'Subtheme based on ProudTheme, Bootstrap, the ProudCity Pattern Library and Radix.', "$description");
  }
  else {
    drush_op('proudtheme_file_str_replace', "$subtheme_path/$machine_name.info", 'Subtheme based', "$description based");
  }
  // Create the template.php file with replaced theme name
  drush_op('proudtheme_file_str_replace', "$subtheme_path/template.php", 'proud_subtheme', "$machine_name");
  // Rename the Drupal behavior name in the custom js file.
  drush_op('proudtheme_file_str_replace', "$subtheme_path/js/scripts.js", 'proud_subtheme', "$machine_name");
  // Rename functions in template.php
  drush_op('proudtheme_file_str_replace', "$subtheme_path/template.php", 'proud_subtheme', "$machine_name");
  // Rename functions in theme-settings.php
  drush_op('proudtheme_file_str_replace', "$subtheme_path/theme-settings.php", 'proud_subtheme', "$machine_name");

  // Notify user of the newly created theme.
  drush_print(dt("\n!name sub-theme was created in !path. \n",
    array(
      '!name' => $name,
      '!path' => $subtheme_path,
    )
  ));
    // Notify user of the newly created theme.
  drush_print(dt("\nYou may need to set permissions on the new theme.\nsudo chown -R MYUSER:MYUSER !name.\n",
    array(
      '!name' => $name
    )
  ));
  drush_pm_enable_validate($machine_name);
  drush_pm_enable($machine_name);
}

/**
 * Internal helper: Replace strings in a file.
 */
function proudtheme_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}

/**
 * Implements hook_drush_help().
 */
function proudtheme_drush_help($section) {
  switch ($section) {
    case 'drush:proud-sub-theme':
      return dt("Create a ProudTheme custom sub-theme.");
  }
}
