#!/usr/bin/python3

import sys, os
import json

import getpass
import re
import urllib.request
from collections import OrderedDict
from bs4 import BeautifulSoup

import http.cookiejar

def normalized(content):
  return content.strip().replace('\r', '') + "\n"

def is_japanese(ch):
  # Thank you!
  # http://minus9d.hatenablog.com/entry/2015/07/16/231608
  try:
    name = unicodedata.name(ch)
    if "CJK UNIFIED" in name or "HIRAGANA" in name or "KATAKANA" in name:
      return True
  except ValueError:
    pass
  return False

def pure_japanese_text(content):
  return "".join([x for x in content if is_japanese(x)])

class LoginError(Exception):
  pass


class SampleParseError(Exception):
  pass


class InputParseError(Exception):
  pass


class AtCoder:
  def __init__(self):
    self.cj = http.cookiejar.CookieJar()

    self.opener = urllib.request.build_opener(
      urllib.request.HTTPCookieProcessor(self.cj))

  def login(self, username=None, password=None):
    req = self.opener.open('https://beta.atcoder.jp/login')
    soup = BeautifulSoup(req,'html.parser')
    tags = soup.select('input[name=csrf_token]')
    csrf_token = tags[0].get('value') if len(tags) >= 1 else None
    if csrf_token is None:
      raise LoginError('csrf_token is not found.')

    if username is None:
      username = input('AtCoder username: ')

    if password is None:
      password = getpass.getpass('AtCoder password: ')

    postdata = {
      'csrf_token': csrf_token,
      'username': username,
      'password': password
    }
    encoded_postdata = urllib.parse.urlencode(postdata).encode('utf-8')
    req = self.opener.open(
      'https://beta.atcoder.jp/login', encoded_postdata)
    html = req.read().decode('utf-8')
    if html.find("<h2>ログイン</h2>") != -1 or html.find('<h2>Sign In</h2>') != -1:
      raise LoginError
    return True

  def get_problem_list(self, contestid):
    """
        入力
            contestid#str : https://beta.atcoder.jp/contests/***/)だったら***の部分
        出力
            #OrderedDict<str:str> : 問題番号("A","B","C",..)→URLのディクショナリ
    """
    req = self.opener.open(
      'https://beta.atcoder.jp/contests/{contestid}/tasks'.format(contestid=contestid)
    )
    soup = BeautifulSoup(req, "html.parser")

    res = OrderedDict()
    for tag in soup.select('div.col-sm-12 table td a')[0::3]:
      res[tag.text] = 'https://beta.atcoder.jp' + tag.get("href")
    return res

  def get_all(self, url):
    """
        入力
            url#str : 問題ページのURL
        出力
            #(str,list((str,str))) : 指定したページから得られた(入力形式,[(サンプル入力1,出力1),(サンプル入力2,出力2)...]のリスト)の組
    """
    req = self.opener.open(url)
    soup = BeautifulSoup(req, "html.parser")

    # 英語のほうタグ削除
    for e in soup.findAll("span", {"class": "lang-en"}):
      e.extract()

    # AtCoder Formatぽかったらそっちはpartタグがついてていい感じなので，そっちを解析する
    soup_tmp = soup.select('.part')
    if soup_tmp:
      soup_tmp[0].extract()

    def detection_algorithm1():
      input_tags = []
      output_tags = []
      input_format_tag = None
      for tag in soup.select('section'):
        h3tag = tag.find('h3')
        if h3tag is None:
          continue
        # 何かいくつかの問題のh3タグ内に変な特殊文字が混じっていてやばい
        section_title = pure_japanese_text(tag.find('h3').get_text())

        if section_title.startswith("入力例"):
          input_tags.append(tag.find('pre'))
        elif section_title.startswith("入力"):
          input_format_tag = tag.find('pre')

        if section_title.startswith("出力例"):
          output_tags.append(tag.find('pre'))
      return input_format_tag, input_tags, output_tags

    def detection_algorithm2():
      pretags = soup.select('pre')

      sample_tags = pretags[1:]
      input_tags = sample_tags[0::2]
      output_tags = sample_tags[1::2]
      input_format_tag = pretags[0]
      return input_format_tag, input_tags, output_tags

    try:
      input_format_tag, input_tags, output_tags = detection_algorithm1()
      if input_format_tag is None:
        raise InputParseError
    except Exception:
      input_format_tag, input_tags, output_tags = detection_algorithm2()

    if len(input_tags) != len(output_tags):
      raise SampleParseError
    res = [(normalized(in_tag.text), normalized(out_tag.text))
         for in_tag, out_tag in zip(input_tags, output_tags)]

    if input_format_tag is None:
      raise InputParseError

    input_format = normalized(input_format_tag.text)

    return input_format, res

  def get_samples(self, url):
    """
        入力
            url#str : 問題ページのURL
        出力
             #list((str,str) : [(サンプル入力1,出力1),(サンプル入力2,出力2)...]のリスト
        コメント
            get_all()関数のwrapper
    """
    return self.get_all(url)[1]

  def submit_source_code(self, contestid, taskid, lang, source_code):
    url = 'https://beta.atcoder.jp/contests/{contestid}/submit'.format(contestid=contestid)

    req = self.opener.open(url)
    soup = BeautifulSoup(req, "html.parser")
    csrf_token = soup.find("input", attrs={"name": "csrf_token"}).get("value")

    task_select_area = soup.find('select', attrs={"id": "select-task"})
    task_field_name = task_select_area.get("name")
    # 文字列 "A - " で検査
    task_number = task_select_area.find(
        "option", text=re.compile('%s -' % taskid)).get("value")
    language_field_name = soup.find('div', attrs={"id":"select-lang"}).get('data-name')
    language_select_area = soup.find(
        'div', attrs={"id": "select-lang-%s" % task_number})
    language_number = language_select_area.find(
        "option", text=re.compile(re.escape(lang))).get("value")
    postdata = {
      "csrf_token": csrf_token,
      task_field_name: task_number,
      language_field_name: language_number,
      "sourceCode": source_code
    }
    encoded_postdata = urllib.parse.urlencode(postdata).encode('utf-8')
    req = self.opener.open(url, encoded_postdata)
    return True






def read_config():
  config_path = os.path.join(os.path.dirname(__file__), 'atcoder.config.json')
  with open(config_path, 'r') as f:
    jsonData = json.load(f)
  return jsonData


def makeio(contestid):
  config = read_config()
  print("try to login...", flush=True)
  atcoder = AtCoder()
  atcoder.login(username=config['username'], password=config['password'])
  problems = atcoder.get_problem_list(contestid)

  def write_file(path, content):
    with open(path, 'w') as f:
      f.write(content)
    print('wrote: ' + path, flush=True)

  for problemid, url in problems.items():
    ios = atcoder.get_samples(url)
    input_combined = "\n".join( [ x[0] for x in ios ] )
    output_combined = "\n".join( [ x[1] for x in ios ] )
    write_file('{problemid}.in.txt'.format(problemid=problemid), input_combined)
    write_file('{problemid}.out.txt'.format(problemid=problemid), output_combined)


def submit(taskid, contestid):
  config = read_config()
  source_code = open(str(taskid) + '.cpp').read()
  print("try to login...", flush=True)
  atcoder = AtCoder()
  atcoder.login(username=config['username'], password=config['password'])
  atcoder.submit_source_code(contestid, taskid, config['lang'], source_code)
  print('https://beta.atcoder.jp/contests/{contestid}/submissions/me'.format(contestid=contestid))


def print_usage():
  argv0 = sys.argv[0]
  print("usage:")
  print("    {} makeio [contest_id]".format(argv0))
  print("    {} submit [task_id] [contest_id]".format(argv0))


if __name__ == '__main__':
  '''
    atcoderの問題のサンプル入出力をファイルに保存する。
    betaのサイトから取得。自分用のフォーマットで保存。
    以下のプロジェクトからパクってきた。
    https://github.com/kyuridenamida/atcoder-tools
    
    環境設定
      このファイル (atcoder.py) が置いてある場所と同じフォルダに atcoder.config.json を置く。
      atcoder.config.json の中身は { "username":"xxxx", "password":"yyyy", "lang":"C++14" } な json ファイル。
        
    実行
    
      $ python atcoder.py makeio [contestid]
    成功すればカレントディレクトリに *.in.txt, *.out.txt が作られる。
    
      $ python atcoder.py submit [teskid] [contestid]
    提出する。事故りそう。
    
    たぶん自分の環境でしか役に立たないメモ
    cygwin から windows の python3 を使うには
      $ cmd /C python atcoder.py arc086
    とやるといける。
  '''

  if len(sys.argv) <= 1:
    print_usage()
    sys.exit(1)
  subcommand = sys.argv[1]
  if subcommand == 'makeio':
    if len(sys.argv) <= 2:
      print_usage()
      sys.exit(1)
    contestid = sys.argv[2]
    makeio(contestid)
  elif subcommand == 'submit':
    if len(sys.argv) <= 3:
      print_usage()
      sys.exit(1)
    taskid = sys.argv[2]
    contestid = sys.argv[3]
    submit(taskid, contestid)
