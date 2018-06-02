You must create a Dropbox developer app in order to give your Drupal site access to Dropbox. Follow the instruction below to insure connections work correctly.

### Dropbox Website
1. Create or Login to your Dropbox account. Then visit the developer site at: https://www.dropbox.com/developers.
2. Choose "My apps" from the list on the left.
3. Click the "Create app" button from the top right.
3. Choose Dropbox API. (It is unknown if Dropbox business API will work.)
4. Choose "App folder" access. This will protect the rest of your Dropbox in case your site is compromised.
5. Give your app a name and create it.
6. In your app's detail screen you can further configure if you want. 
7. You will need to generate an API token by selecting the "Generate" button under the OAuth 2 field group.

### Drupal
1. Enable the module.
2. In your Drupal site add a Dropbox destination by going to Configuration -> System -> Backup Migrate -> Settings -> Destinations -> Add Destination (/admin/config/system/backup_migrate/settings/destination/add).
3. Choose "Dropbox" from the off-site destinations list (it will probably be at the bottom).
4. Give your destination a name and enter the access token. You can create an access token in your app by clicking "Generate" Under the OAuth 2 group of your app settings.
5. Dropbox destination should allow backups to Dropbox manually or scheduled. It is usually wise to do a manual backup first, to test your connection, before setting the destination to cron.

### Troubleshooting
1. If you receive out of memory errors use either Drush or the variables module to set the 'backup_migrate_dropbox_upload_limit' variable. Set the variable as high as possible without receiving an out of memory errors to insure maximum performance.
2. If you receive a 4XX error check that the access token is correct or generate a new token and copy it over.
3. If you receive a 5XX error check status.dropbox.com to insure the the server is up and running.
4. If you receive a different error please create a case on the backup_migrate_dropbox module page (https://www.drupal.org/project/backup_migrate_dropbox).
