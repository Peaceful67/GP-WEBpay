<?php

function hook_commerce_payment_method_info() 
{
    $payment_methods['gpwebpay_wps'] = array(
    'base' => 'commerce_gpwebpay_wps',
    'title' => t('GP WebPay WPS'),
    'short_title' => t('Gp Webpay'),
    'description' => t('Gp WebPay Website Payments Standard'),
    'terminal' => FALSE,
    'offsite' => TRUE,
    'offsite_autoredirect' => TRUE,
  );
  return $payment_methods;
}

function commerce_gpwebpay_commerce_payment_method_info() {
  $payment_methods = array();

  $payment_methods['commerce_gpwebpay'] = array(
    'title' => t('GP WebPay'),
    'short_title' => t('GP WebPay'),
    'description' => t('GP WebPay Gateway'),
    'terminal' => FALSE,
    'offsite' => TRUE,
    'offsite_autoredirect' => TRUE,
  ); 
  return $payment_methods;
}

