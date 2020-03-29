<?php

function commerce_gpwebpay_settings_form() {
    $form = array();
 
    $form['commerce_gpwebpay_merchant'] = array(
        '#type' => 'textfield',
        '#title' => t('Merchant ID'),
        '#descripiton' => t('Merchant ID provided by GP WebPay'),
        '#default_value' => variable_get('commerce_gpwebpay_merchant', '---'),
        '#size' => 8,
        '#maxlength' => 8,
        '#required' => true,
    );
    $form['commerce_gpwebpay_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Privat Key'),
        '#descripiton' => t('Merchant KEY provided by GP WebPay'),
        '#default_value' => variable_get('commerce_gpwebpay_key', '---'),
        '#size' => 32,
        '#maxlength' => 32,
        '#required' => true,
    );

    $form['commerce_gpwebpay_url'] = array(
        '#type' => 'textfield',
        '#title' => t('URL'),
        '#descripiton' => t('Server URL of GP WebPay'),
        '#default_value' => variable_get('commerce_gpwebpay_url', 'https://'),
        '#size' => 64,
        '#maxlength' => 128,
        '#required' => true,
    );
    return system_settings_form($form);
}
