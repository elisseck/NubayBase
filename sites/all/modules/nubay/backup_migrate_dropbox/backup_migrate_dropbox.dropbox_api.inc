<?php

/**
 * @file backup_migrate_dropbox.api.inc
 *
 * Dropbox api.
 */

define('BACKUP_MIGRATE_DROPBOX_CONTENT_URL', 'https://content.dropboxapi.com/2/files');

class BackupMigrateDropboxAPI {
  private $token;
  private $upload_session = array();

  public function setToken($token) {
    $this->token = $token;
  }

  public function file_upload($file, $path) {

    // Cut PHP memory limit by 10% to allow for other in memory data.
    $php_memory_limit = intval(backup_migrate_dropbox_byte_size(ini_get('memory_limit')) * 0.9);

    // Dropbox currently has a 150M upload limit per transaction.
    $dropbox_upload_limit = backup_migrate_dropbox_byte_size('150M');

    // For testing or in case the 10% leeway isn't enough allow a smaller upload
    // limit as an advanced setting. This variable has no ui but can be set with
    // drush or through the variable module.
    $manual_upload_limit = backup_migrate_dropbox_byte_size(variable_get('backup_migrate_dropbox_upload_limit', '150M'));

    // Use the smallest value for the max file size.
    $max_file_size = min($php_memory_limit, $dropbox_upload_limit, $manual_upload_limit);

    // File.
    $file_size = filesize($file);

    // If the file size is greater than
    if ($file_size > $max_file_size) {
      // Open file.
      $file_handle = fopen($file, 'rb');
      if (!$file_handle) {
        throw new ErrorException('Cannot open backup file (1).');
      }

      // Start.
      $content = fread($file_handle, $max_file_size);
      if (!$content) {
        throw new ErrorException('Cannot read backup file (2).');
      }
      $this->_file_upload_session_start($content);

      // Append.
      while (!feof($file_handle)) {
        // Get content.
        $content = fread($file_handle, $max_file_size);
        if (!$content) {
          throw new ErrorException('Cannot read backup file (3).');
        }
        $this->_file_upload_session_append($content);
      }

      // Finish.
      $this->_file_upload_session_finish($path);
    }
    else {
      $content = file_get_contents($file);
      if (!$content) {
        throw new ErrorException('Cannot open backup file (4).');
      }
      $this->_file_upload_upload($path, $content);
    }
  }

  private function _file_upload_session_start($content) {
    // Header.
    $header = array();
    $header[] = 'Content-type: application/octet-stream';
    $header[] = 'Authorization: Bearer ' . $this->token;
    $header[] = 'Accept: application/json';

    // Curl.
    $request = curl_init();
    curl_setopt($request, CURLOPT_URL, BACKUP_MIGRATE_DROPBOX_CONTENT_URL . '/upload_session/start');
    curl_setopt($request, CURLOPT_POST, 1);
    curl_setopt($request, CURLOPT_HTTPHEADER, $header);
    curl_setopt($request, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($request, CURLOPT_POSTFIELDS, $content);
    $result = json_decode($this->_execute_curl($request), TRUE);

    // Catch any errors.
    if(!is_array($result) || !isset($result['session_id'])) {
      throw new ErrorException('No session id returned.');
    }

    curl_close($request);

    $this->upload_session['session_id'] = $result['session_id'];
    $this->upload_session['offset'] = strlen($content);
  }

  private function _file_upload_session_append($content) {
    // Args.
    $parameters = array(
      'cursor' => $this->upload_session,
    );

    // Header.
    $header = array();
    $header[] = 'Content-type: application/octet-stream';
    $header[] = 'Authorization: Bearer ' . $this->token;
    $header[] = 'Dropbox-API-Arg: ' . json_encode($parameters);
    $header[] = 'Accept: application/json';

    // Curl.
    $request = curl_init();
    curl_setopt($request, CURLOPT_URL, BACKUP_MIGRATE_DROPBOX_CONTENT_URL . '/upload_session/append_v2');
    curl_setopt($request, CURLOPT_POST, 1);
    curl_setopt($request, CURLOPT_HTTPHEADER, $header);
    curl_setopt($request, CURLOPT_POSTFIELDS, $content);
    curl_setopt($request, CURLOPT_RETURNTRANSFER, TRUE);
    $this->_execute_curl($request);


    curl_close($request);
    $this->upload_session['offset'] += strlen($content);
  }

  private function _file_upload_session_finish($path) {
    // Finish.
    $parameters = array(
      'cursor' => $this->upload_session,
      'commit' => array(
        'path' => $path,
        'mode' => 'add',
        'autorename' => TRUE,
        'mute' => TRUE,
      ),
    );

    $header = array();
    $header[] = 'Content-type: application/octet-stream';
    $header[] = 'Authorization: Bearer ' . $this->token;
    $header[] = 'Dropbox-API-Arg: ' . json_encode($parameters);
    $header[] = 'Accept: application/json';

    $request = curl_init();
    curl_setopt($request, CURLOPT_URL, BACKUP_MIGRATE_DROPBOX_CONTENT_URL . '/upload_session/finish');
    curl_setopt($request, CURLOPT_POST, 1);
    curl_setopt($request, CURLOPT_HTTPHEADER, $header);
    curl_setopt($request, CURLOPT_RETURNTRANSFER, TRUE);
    $this->_execute_curl($request);


    curl_close($request);
  }

  private function _file_upload_upload($path, $content)
  {
    // Simple upload.
    $parameters = array(
      'path' => $path,
      'mode' => 'add',
      'autorename' => TRUE,
      'mute' => FALSE,
    );

    // Header.
    $header = array();
    $header[] = 'Content-type: application/octet-stream';
    $header[] = 'Authorization: Bearer ' . $this->token;
    $header[] = 'Dropbox-API-Arg: ' . json_encode($parameters);
    $header[] = 'Accept: application/json';

    // Curl.
    $request = curl_init();
    curl_setopt($request, CURLOPT_URL, BACKUP_MIGRATE_DROPBOX_CONTENT_URL . '/upload');
    curl_setopt($request, CURLOPT_POST, 1);
    curl_setopt($request, CURLOPT_HTTPHEADER, $header);
    curl_setopt($request, CURLOPT_POSTFIELDS, $content);
    curl_setopt($request, CURLOPT_RETURNTRANSFER, TRUE);
    $this->_execute_curl($request);

    curl_close($request);
  }

  private function _execute_curl($request)
  {
    $result = curl_exec($request);

    $response_code = curl_getinfo($request, CURLINFO_HTTP_CODE);
    if(curl_error($request)) {
      throw new ErrorException('Curl error: ' . curl_error($request));
    }
    elseif(isset($result['error'])) {
      $result = json_decode($result);
      throw new ErrorException('Dropbox error: ' . $result['error_summary']);
    }
    elseif($response_code >= 500) {
      throw new ErrorException('Dropbox server error. Try later or check status.dropbox.com for outages.');
    }
    elseif($response_code >= 400) {
      throw new ErrorException('Bad http status response code (' . $response_code . '): ' . $result);
    }

    return $result;
  }
}

// Pulled from Stack Overflow: http://stackoverflow.com/q/1336581/819883.
function backup_migrate_dropbox_byte_size($byteString)
{
  preg_match('/^\s*([0-9.]+)\s*([KMGT])B?\s*$/i', $byteString, $matches);

  if (!(count($matches) >= 3))
  {
    return 0;
  }
  $num = (float)$matches[1];
  switch (strtoupper($matches[2]))
  {
    /** @noinspection PhpMissingBreakStatementInspection */
    case 'T':
      $num *= DRUPAL_KILOBYTE;
    /** @noinspection PhpMissingBreakStatementInspection */
    case 'G':
      $num *= DRUPAL_KILOBYTE;
    /** @noinspection PhpMissingBreakStatementInspection */
    case 'M':
      $num *= DRUPAL_KILOBYTE;
    case 'K':
      $num *= DRUPAL_KILOBYTE;
  }

  return intval($num);
}
