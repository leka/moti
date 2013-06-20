#!/usr/local/bin ruby

require 'fileutils'

# FileUtils.ln_s Dir.glob('../lib/'), '~/Documents/Arduino/libraries/'

a = File.expand_path(File.dirname(__FILE__))

print a

print "\n"

b = a.sub!('script','') + "lib/"

print b

print "\n"

FileUtils.ln_s(Dir.glob(b),'~/Documents/Arduino/libraries/')

