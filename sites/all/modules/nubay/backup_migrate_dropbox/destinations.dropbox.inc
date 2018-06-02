<?php

/**
 * @file destinations.dropbox.inc
 *
 * Functions to handle the dropbox backup destination.
 */

/**
 * A destination for sending database backups to a Dropbox account.
 *
 * @ingroup backup_migrate_destinations
 */
class backup_migrate_destination_dropbox extends backup_migrate_destination_remote {
  var $supported_ops = array('scheduled backup', 'manual backup', 'remote backup', 'configure');

  /**
   * Save to to the Dropbox destination.
   */
  function save_file($file, $settings) {

    // Set up a temporary file to transfer up to dropbox.
    $filename = $file->file_info['filename'] . '.' . implode('.', $file->ext);
    $destination_filename = realpath(variable_get('file_temporary_path', '')) . '/' . $filename;
    rename($file->filepath(), $destination_filename);

    // Initialize the dropbox api.
    module_load_include('inc', 'backup_migrate_dropbox', 'backup_migrate_dropbox.dropbox_api');
    $dropbox_api = new BackupMigrateDropboxAPI();

    $token = $this->settings('token');
    $dropbox_api->setToken($token);
    $path = '/' . $this->dest_url['path'] . '/' . $filename;

    try {
      $dropbox_api->file_upload($destination_filename, $path);
    }
    catch(exception $e) {
      watchdog('backup_migrate', 'Backup Migrate Dropbox Error: ' . $e->getMessage(), array(), WATCHDOG_ERROR);
      drupal_set_message('Backup Migrate Dropbox Error: ' . $e->getMessage(), 'error');
      return NULL;
    }

    return $file;
  }

  /**
   * Get the form for the settings for this filter.
   */
  function edit_form() {
    $form = parent::edit_form();

    $form['description'] = array(
      '#type' => 'markup',
      '#weight' => -999,
      '#markup' => t('<p>In order to use your DropBox account as a Backup and Migrate destination,
        you must create a DropBox App and obtain an application token and enter it below.
        <ol>
          <li>Create a DropBox App by logging into your DropBox account and going to
              <a href="https://www.dropbox.com/developers/apps">https://www.dropbox.com/developers/apps</a>.</li>
          <li>Click the button to "Create an app". Be sure to give your app a descriptive name,
              as the name you give it will be part of the path within your DropBox folder. For example,
              if you create an app called "kittens", then DropBox will create a DropBox/Apps/kittens
              directory in your DropBox folder.</li>
          <li>In the OAuth 2 section of your app settings you will see a button that says "Generate Access Token".
              Click this button. Copy the entire token and paste it into the Token below.</li>
        </ol></p>'),
    );

    $form['name']['#description'] = t('Enter a "friendly" name for this destination. Only appears as a descriptor in the Backup and Migrate administration screens.');

    $form['scheme'] = array(
      '#type' => 'value',
      '#value' => 'https',
    );

    $form['host'] = array(
      '#type' => 'value',
      '#value' => 'www.dropbox.com',
    );

    $form['path']['#description'] = t('A relative folder inside your Dropbox App folder. For example, Dropbox/Apps/(your app name)/(whatever path you enter here). Do not you slashes before or after the path.');
    $form['path']['#required'] = FALSE;

    $form['user'] = array(
      '#type' => 'value',
      '#value' => '',
    );

    $form['old_password'] = array(
      '#type' => 'value',
      '#value' => '',
    );

    $form['pass'] = array(
      '#type' => 'value',
      '#value' => '',
    );

    $form['settings']['token'] = array(
      '#type' => 'textfield',
      '#title' => 'Dropbox App Token',
      '#description' => 'Generated access token from your app. <b>Do not</b> use the secret key.',
      '#required' => TRUE,
      "#default_value" => $this->settings('token'),
    );

    $form['settings']['#weight'] = 60;

    return $form;
  }

  /**
   * Submit the form for the settings for the files destination.
   */
  function edit_form_submit($form, &$form_state) {
    // Add the token.
    $form_state['values']['settings']['token'] = $form_state['values']['token'];
    parent::edit_form_submit($form, $form_state);
  }
}
