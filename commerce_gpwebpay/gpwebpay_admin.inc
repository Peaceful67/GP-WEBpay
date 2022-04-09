<?php

include_once 'settings.inc';

function commerce_gpwebpay_settings_form() {
    $form = array();

    $key_filename = getcwd() . base_path() . drupal_get_path('module', 'commerce_gpwebpay') . PRIVATE_KEY;

    $form['commerce_gpwebpay_merchant'] = array(
        '#type' => 'textfield',
        '#title' => t('Merchant ID'),
        '#descripiton' => t('Merchant ID provided by GP WebPay'),
        '#default_value' => variable_get('commerce_gpwebpay_merchant', '---'),
        '#size' => 12,
        '#maxlength' => 16,
        '#required' => true,
    );
    $form['commerce_gpwebpay_passwd'] = array(
        '#type' => 'textfield',
        '#title' => t('Password for Privat Key'),
        '#descripiton' => t('password for merchant private key provided by GP WebPay'),
        '#default_value' => variable_get('commerce_gpwebpay_passwd', '---'),
        '#size' => 32,
        '#maxlength' => 32,
        '#required' => true,
    );
    $form['commerce_gpwebpay_private_key'] = array(
        '#title' => t('Private Key File'),
        '#type' => 'file',
        '#description' => t(is_file($key_filename) ? 'Private key is uploaded' : 'Missing private key'),
        '#upload_validators' => [
            'file_validate_size' => [2000],
        ],
    );
    $form['commerce_gpwebpay_public_key'] = [
        '#type' => 'radios',
        '#title' => 'Payment gateway',
        '#options' => [
            0 => 'Test, URL: '.GP_TEST_URL,
            1 => 'Production, URL: '.GP_PRODUCTION_URL,
        ],
        '#default_value' => variable_get('commerce_gpwebpay_public_key', 0),
    ];
    $form['commerce_gpwebpay_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => t('Payment method enabled'),
        '#descripiton' => t('GP WEBPay gateway enabled'),
        '#default_value' => variable_get('commerce_gpwebpay_enabled', 1),
        '#required' => false,
    );
    $form['addinfo_version'] = [
        '#type' => 'item',
        '#title' => t('Addinfo version'),
        '#markup' => ADDINFO_VERSION,
    ];
    $form['#submit'][] = 'commerce_gpwebpay_settings_form_submit';
    return system_settings_form($form);
}

function commerce_gpwebpay_settings_form_submit($form, &$form_state) {

    if (empty($_FILES['files']['name']['commerce_gpwebpay_private_key'])) {
        return;
    }
    $file = file_save_upload('commerce_gpwebpay_private_key', array('file_validate_extensions' => ['key']));
    $destination = getcwd() . base_path() . drupal_get_path('module', 'commerce_gpwebpay') . PRIVATE_KEY;
    $dirname = drupal_dirname($destination);
    watchdog('file', 'GPWEBpay key file is uploaded');
    if (!file_prepare_directory($dirname)) {
        watchdog('file', 'GPWEBpay key file destination directory is not writeable. Trying to chmod...');
        if (!drupal_chmod($dirname, '0777')) {
            drupal_set_message(t('Upload of key file is unsuccessful due to unwriteble destionation directory'));
            return;
        }
    }
    $new_file = file_unmanaged_move($file->uri, $destination, FILE_EXISTS_REPLACE);
}
