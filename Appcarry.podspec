Pod::Spec.new do |s|
   s.name                     = 'Appcarry'
   s.version                  = '1.0.0'
   s.summary                  = 'Appcarry Attribution and Analytics ios SDK'
   s.description              = <<-DESC
   Appcarry native track allows you to find what attracts new users to your app,
   measure all your app marketing activities on one dashboard, and add new traffic sources in minutes,
   all without having to update SDK.
   DESC
   s.homepage                 = 'https://appcarry.com'
   s.author                   = {'Appcarry Team' => 'info@appcarry.com'}
   s.license                  = { :type => 'Proprietary', :text => 'Copyright 2021 Appcarry Private Limited All rights reserved.' }
   s.source                   = { :git => 'git@github.com:appcarry/AppcarryFramework.git', :tag => s.version.to_s }  
   s.requires_arc             = true
   s.platform                 = :ios

   s.ios.deployment_target    = '11.0'
   s.ios.vendored_frameworks  = 'AppcarryFramework.framework'  
   s.ios.frameworks           = 'Security', 'SystemConfiguration'
end