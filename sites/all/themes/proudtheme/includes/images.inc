<?php


function proudtheme_add_inverted_logo(&$form, &$form_state) {
  $form['proudtheme_inverted_logo'] = array(
    '#title' => t('Inverted logo'),
    '#type' => 'managed_file',
    '#description' => t('Inverted logo should look good on a dark backgound.'),
    '#default_value' => variable_get('proudtheme_inverted_logo', ''),
    '#field_name' => 'proudtheme_inverted_logo',
    '#upload_location' => 'public://inverted_logo/'
  );
  $form_state['build_info']['files'][] = drupal_get_path('theme', 'proudtheme') . '/includes/images.inc';
  $form['#submit'][] = 'proudtheme_save_inverted_logo';
}

function proudtheme_save_inverted_logo(&$form, &$form_state) {
  $image_fid = $form_state['values']['proudtheme_inverted_logo'];
  $image = file_load($image_fid);
  if (is_object($image)) {
    // Check to make sure that the file is set to be permanent.
    if ($image->status == 0) {
      // Update the status.
      $image->status = FILE_STATUS_PERMANENT;
      // Save the update.
      file_save($image);
      // Add a reference to prevent warnings.
      file_usage_add($image, 'proudtheme', 'theme', 1);
      variable_set('proudtheme_inverted_logo', $image_fid);
     }
  }
}

function proudtheme_get_inverted_logo() {
  $image_fid = variable_get('proudtheme_inverted_logo', FALSE);
  if(!$image_fid) {
    return FALSE;
  }
  return file_create_url(file_load($image_fid)->uri);
}
