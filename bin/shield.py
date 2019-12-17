#!/usr/bin/python3

# Copyright (C) 2019 SCARV project <info@scarv.org>
#
# Use of this source code is restricted per the MIT license, a copy of which
# can be found at https://opensource.org/licenses/MIT (or should be included
# as LICENSE.txt within the associated archive or repository).

import json, os, re, shutil, subprocess, urllib.parse

def parse_conf() :
  if ( not os.path.isfile( 'sca3s.json' ) ) :
    return { 'enable' : false }
  else :
    return json.load( open( 'sca3s.json', 'r' ) )

def parse_repo() :
  repo_url    = subprocess.check_output( [ 'git', 'config', '--get', 'remote.origin.url' ] ).decode().strip()
  repo_branch = subprocess.check_output( [ 'git', 'rev-parse', '--abbrev-ref', 'HEAD'    ] ).decode().strip()
  
  t = re.match( '/?(?P<repo_owner>[-\w]+)/?(?P<repo_name>[-\w]+)(.git)?', urllib.parse.urlparse( repo_url ).path )

  if ( t == None ) :
    return None
  else :
    return { 'repo_branch' : repo_branch, 'repo_owner' : t.group( 'repo_owner' ),
                                          'repo_name'  : t.group( 'repo_name'  ) }

if ( __name__ == '__main__' ) :
  conf = parse_conf() ; repo = parse_repo()
  
  if ( ( not conf[ 'enable' ] ) or ( not os.path.isfile( 'README.md' ) ) ) :
    exit( 0 )
  
  fd_readme_old = open(       'README.md', 'r' )
  fd_readme_new = open( 'build/README.md', 'w' )
  
  marker_line = '<!--- SCA3S shields -->'
  marker_flag = False
  
  for line in fd_readme_old.readlines() :
    line = line.strip()
  
    if   ( ( marker_flag == False ) and ( line != marker_line ) ) :
      print( line, file = fd_readme_new )
  
    elif ( ( marker_flag == False ) and ( line == marker_line ) ) :
      marker_flag =  True
    elif ( ( marker_flag == True  ) and ( line == marker_line ) ) :
      marker_flag = False
  
      def shield( x ) :
        print( x.format( **repo ), file = fd_readme_new )
  
      print( marker_line, file = fd_readme_new )
  
      shield( '[![Documentation](https://codedocs.xyz/{repo_owner}/{repo_name}.svg)](https://codedocs.xyz/{repo_owner}/{repo_name})' )
  
      shield( '[![SCA3S acquire data](https://lab.scarv.org/api/shields/acquire/{repo_owner}/{repo_name}/{repo_branch})](...)' )
      shield( '[![SCA3S analyse data](https://lab.scarv.org/api/shields/analyse/{repo_owner}/{repo_name}/{repo_branch})](...)' )
  
      print( marker_line, file = fd_readme_new )
  
  fd_readme_old.close()
  fd_readme_new.close()
  
  shutil.move( 'build/README.md', 'README.md' )
