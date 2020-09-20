#include <stdio.h>
#include <drawlib.h>

int main (void) {

  dl_initialize(1.0);
  /*背景*/
  dl_clear(dl_color_from_name("white"));
  dl_circle(640, 0, 620,dl_color_from_name("black"), 1, 1);
  /*盤*/
  dl_rectangle(214, 46, 591, 439,dl_color_from_name("black"),1,1);
  dl_rectangle(217, 49, 588, 436,dl_color_from_name("white"),1,1);
  dl_rectangle(223, 55, 582, 430,dl_color_from_rgb(33, 113, 46),1,1);
  dl_rectangle(223, 55, 582, 430,dl_color_from_name("black"),5,0);
  dl_rectangle(268, 55, 537, 430,dl_color_from_name("black"),5,0);  
  dl_rectangle(313, 55, 492, 430,dl_color_from_name("black"),5,0);
  dl_rectangle(358, 55, 447, 430,dl_color_from_name("black"),5,0);
  dl_rectangle(400, 55, 405, 430,dl_color_from_name("black"),1,1);
  dl_rectangle(223, 108, 582, 377,dl_color_from_name("black"),5,0);
  dl_rectangle(223, 153, 582, 332,dl_color_from_name("black"),5,0);
  dl_rectangle(223, 198, 582, 287,dl_color_from_name("black"),5,0);
  dl_rectangle(223, 240, 582, 245,dl_color_from_name("black"), 1, 1);
  /*石の個数欄*/
  dl_rectangle(25, 170, 175, 275,dl_color_from_rgb(31, 55, 57), 1, 1);
  dl_rectangle(30, 175, 170, 270,dl_color_from_rgb(79, 124, 128), 1, 1);
  dl_circle(58, 195, 16,dl_color_from_name("black"), 1, 1);
  dl_circle(58, 250, 16,dl_color_from_name("white"), 1, 1);
  dl_text("x", 88, 205, 1,dl_color_from_name("black"), 2);
  dl_text("x", 88, 260, 1,dl_color_from_name("black"), 2);
  /*passボタン*/
  dl_rectangle(50, 380, 150, 410,dl_color_from_name("black"), 1, 1);
  dl_rectangle(50, 380, 150, 410,dl_color_from_name("white"), 1, 0);
  dl_text("PASS", 60, 405, 1,dl_color_from_name("white"), 1);
  /*終了ボタン*/
  dl_rectangle(100, 435, 200, 465,dl_color_from_name("black"), 1, 1);
  dl_rectangle(100, 435, 200, 465,dl_color_from_name("white"), 1, 0);
  dl_text("CLOSE", 110, 460, 0.8,dl_color_from_name("white"), 1);

  int bord[10][10] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int b, w, turn, sta, m, i, num, k, l, y = 0, x = 0, y1, x1, xc, yc, xi, yi, t, xt, px, py, xmin, xmax, ymin, ymax, cx, cy, in, p = 1, cl = 0;
  char bd[11], wd[11];
  float fc, sc, ac, bc, cr;
  
  /*白＝1　黒＝2*/
  
  /*中心の石の初期位置*/
  dl_circle(380, 220, 16,dl_color_from_name("white"), 1, 1);
  dl_circle(425, 220, 16,dl_color_from_name("black"), 1, 1);
  dl_circle(380, 265, 16,dl_color_from_name("black"), 1, 1);
  dl_circle(425, 265, 16,dl_color_from_name("white"), 1, 1);
  bord[4][4] = 1;
  bord[4][5] = 2;
  bord[5][4] = 2;
  bord[5][5] = 1;
  
  /*黒石と白石の初期の個数*/
  b = 2;
  w = 2;
  dl_text("2", 118, 205, 1,dl_color_from_name("black"), 2);
  dl_text("2", 118, 260, 1,dl_color_from_name("black"), 2);

  /*手番(黒を先行とする)*/
  turn = 1;
  sta = 2;

  while (w + b != 64 && cl == 0) {
    i = 0;
    /*手番を交代*/
    m = turn;
    turn = sta;
    sta = m;
    if (turn == 2) {
      dl_rectangle(30, 175, 35, 220,dl_color_from_name("black"), 1, 1);
      dl_rectangle(30, 225, 35, 270,dl_color_from_rgb(79, 124, 128), 1, 1);
    }
    else {
      dl_rectangle(30, 175, 35, 220,dl_color_from_rgb(79, 124, 128), 1, 1);
      dl_rectangle(30, 225, 35, 270,dl_color_from_name("white"), 1, 1);
    }
  
    while (i == 0) {
      i = 0;
      in = 0;
      xt = 0;
      
      /*クリックした位置のx,y座標を読み込む（石を置く位置を入力）*/
      while (in != 1){
        if (dl_get_event(&t, &k, &xc, &yc)) {
          if (t == DL_EVENT_L_UP) {
            xi = xc;
            yi = yc;
            in = 1;
          }
        }
      }
      
      /*pass*/      
      if (50 < xi && xi < 150 && 380 < yi && yi < 410 && p > 0) {
        i = 1;
        p = 0;
      }
      /*close*/
      if (100 < xi && xi < 200 && 435 < yi && yi < 465) {
        cl = 1;
        i = 1;
      }
      
      /*読み込んだ座標をbord[x][y]に合わせて変換*/
      
      for (px = 1, xmin = 225, xmax = 265; xmax <= 628; px += 1, xmin += 45, xmax += 45) {
        if (xmin <= xi && xi <= xmax) {
          x = px;
          xt = 1;
        }
      }
      if (xt == 1) {
        for (py = 1, ymin = 65, ymax = 105; ymax <= 465; py += 1, ymin += 45, ymax += 45) {
          if (ymin <= yi && yi <= ymax) {
            y = py;
            in = 2;
          }
        }
      }

      if (bord[x][y] == 0 && in == 2) {
      
          /*石の入れ替えの判定*/    
        for (num = 0; num < 8; ++num) {
          if (num == 0) {
            y1 = y;
            x1 = x;
            --y1;
            --x1;
            if (bord[x1][y1] == sta) {
              --y1;
              --x1;
              
              for (k = 0, l = 1; k == 0; --y1, --x1, ++l) {
                if (y1 == 0 || x1 == 0 || y1 == 9 || x1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    ++y1;
                    ++x1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 1) {
            y1 = y;
            x1 = x;
            --x1;
            if (bord[x1][y1] == sta) {
              --x1;
              
              for (k = 0, l = 1; k == 0; --x1, ++l) {
                if (x1 == 0 || x1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    ++x1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 2) {
            y1 = y;
            x1 = x;
            ++y1;
            --x1;
            if (bord[x1][y1] == sta) {
              ++y1;
              --x1;
              
              for (k = 0, l = 1; k == 0; ++y1, --x1, ++l) {
                if (y1 == 0 || x1 == 0 || y1 == 9 || x1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    --y1;
                    ++x1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 3) {
            y1 = y;
            x1 = x;
            --y1;
            if (bord[x1][y1] == sta) {
              --y1;
              
              for (k = 0, l = 1; k == 0; --y1, ++l) {
                if (y1 == 0 || y1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    ++y1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 4) {
            y1 = y;
            x1 = x;
            ++y1;
            if (bord[x1][y1] == sta) {
              ++y1;
              
              for (k = 0, l = 1; k == 0; ++y1, ++l) {
                if (y1 == 0 || y1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    --y1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 5) {
            y1 = y;
            x1 = x;
            --y1;
            ++x1;
            if (bord[x1][y1] == sta) {
              --y1;
              ++x1;
              
              for (k = 0, l = 1; k == 0; --y1, ++x1, ++l) {
                if (y1 == 0 || x1 == 0 || y1 == 9 || x1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    ++y1;
                    --x1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 6) {
            y1 = y;
            x1 = x;
            ++x1;
            if (bord[x1][y1] == sta) {
              ++x1;
              
              for (k = 0, l = 1; k == 0; ++x1, ++l) {
                if (x1 == 0 || x1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    --x1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
          if (num == 7) {
            y1 = y;
            x1 = x;
            ++y1;
            ++x1;
            if (bord[x1][y1] == sta) {
              ++y1;
              ++x1;
              
              for (k = 0, l = 1; k == 0; ++y1, ++x1, ++l) {
                if (y1 == 0 || x1 == 0 || y1 == 9 || x1 == 9 || bord[x1][y1] == 0) ++k;
                else if (bord[x1][y1] == turn) {
                  l += 2;
                  
                  for (; l > 0; --l) {
                    bord[x1][y1] = turn;
                    --y1;
                    --x1;
                  }
                  ++k;
                  ++i;
                  ++p;
                }
              }
            }
          }
        }
      }
      
      dl_rectangle(217, 49, 588, 436,dl_color_from_name("white"),2,0);
      if (i == 0) {
        dl_rectangle(217, 49, 588, 436,dl_color_from_name("red"),2,0);
      }
      /*黒と白の石を表示*/
      
      for (x = 1; x < 9; ++x) {
        for (y = 1; y < 9; ++y) {
          cx = 200 + 45 * x;
          cy = 40 + 45 * y;
          if (bord[x][y] == 1) {
            dl_circle(cx, cy, 16,dl_color_from_name("white"), 1, 1);
            }
          else if (bord[x][y] == 2) {
            dl_circle(cx, cy, 16,dl_color_from_name("black"), 1, 1);
          }
        }
      }
    }
  /*黒石と白石のそれぞれの数を表示*/
    if (i != 0) {
      for (b = 0, w = 0, x = 1; x < 9; ++x) {
        for (y = 1; y < 9; ++y) {
          if (bord[x][y] == 2) b++;
          if (bord[x][y] == 1) w++;
        }
      }
    }
  sprintf(bd, "%d", b);
  sprintf(wd, "%d", w);
  dl_rectangle(120, 175, 170, 270,dl_color_from_rgb(79, 124, 128), 1, 1);
  dl_text(bd, 118, 205, 1,dl_color_from_name("black"), 2);
  dl_text(wd, 118, 260, 1,dl_color_from_name("black"), 2);
  }
  
  
  /*勝敗を判定*/
  if (w < b) {
    for (fc = 215, sc = 215; fc > 159; fc -= 0.1, sc += 0.1) {
      dl_rectangle(0, fc, 640, fc - 0.1,dl_color_from_name("white"),1,1);
      dl_rectangle(0, sc, 640, sc + 0.1,dl_color_from_name("black"),1,1);
    }
    dl_text("Black Win", 45, 255, 3.5,dl_color_from_rgb(91, 53, 133), 10);
    dl_text("Black Win", 45, 255, 3.5,dl_color_from_name("black"), 3);
    for (bc = -5, ac = 645; bc < 645; bc += 0.1, ac -= 0.1) {
      dl_rectangle(ac + 1, 160, ac, 0,dl_color_from_rgb(88, 88, 88),1,1);
      dl_rectangle(bc - 1, 270, bc, 640,dl_color_from_rgb(48, 48, 48),1,1);
    }
    sprintf (bd, "black=%d", b);
    sprintf (wd, "white=%d", w);
    dl_text(bd, 80, 120, 2,dl_color_from_name("black"), 3);
    dl_text(wd, 450, 120, 1,dl_color_from_name("white"), 2);
    dl_circle(55, 105, 16,dl_color_from_name("black"), 1, 1);
    dl_circle(435, 115, 8,dl_color_from_name("white"), 1, 1);
    for (cr = 460; cr > 331; cr -= 0.01) dl_circle(320, 250, cr,dl_color_from_name("black"), 0.5, 0);
  }
  else if (w > b) {
  for (fc = 215, sc = 215; fc > 159; fc -= 0.1, sc += 0.1) {
      dl_rectangle(0, fc, 640, fc - 0.1,dl_color_from_name("white"),1,1);
      dl_rectangle(0, sc, 640, sc + 0.1,dl_color_from_name("black"),1,1);
    }
    dl_text("White Win", 45, 255, 3.5,dl_color_from_rgb(91, 53, 133), 10);
    dl_text("White Win", 45, 255, 3.5,dl_color_from_name("white"), 3);
    for (bc = -5, ac = 645; bc < 645; bc += 0.1, ac -= 0.1) {
      dl_rectangle(ac + 1, 160, ac, 0,dl_color_from_rgb(88, 88, 88),1,1);
      dl_rectangle(bc - 1, 270, bc, 640,dl_color_from_rgb(48, 48, 48),1,1);
    }
    sprintf (wd, "white=%d", w);
    sprintf (bd, "black=%d", b);
    dl_text(wd, 80, 120, 2,dl_color_from_name("white"), 3);
    dl_text(bd, 450, 120, 1,dl_color_from_name("black"), 2);
    dl_circle(55, 105, 16,dl_color_from_name("white"), 1, 1);
    dl_circle(435, 115, 8,dl_color_from_name("black"), 1, 1);
    for (cr = 460; cr > 331; cr -= 0.01) dl_circle(320, 250, cr,dl_color_from_name("white"), 0.5, 0);
  }
  else {
  for (fc = 215, sc = 215; fc > 159; fc -= 0.1, sc += 0.1) {
      dl_rectangle(0, fc, 640, fc - 0.1,dl_color_from_name("white"),1,1);
      dl_rectangle(0, sc, 640, sc + 0.1,dl_color_from_name("black"),1,1);
    }
    dl_text("Draw", 180, 255, 3.5,dl_color_from_name("black"), 5);
    dl_text("Draw", 180, 255, 3.5,dl_color_from_name("white"), 3);
    for (bc = -5, ac = 645; bc < 645; bc += 0.1, ac -= 0.1) {
      dl_rectangle(ac + 1, 160, ac, 0,dl_color_from_rgb(88, 88, 88),1,1);
      dl_rectangle(bc - 1, 270, bc, 640,dl_color_from_rgb(48, 48, 48),1,1);
    }
    sprintf (bd, "black=%d", b);
    sprintf (wd, "white=%d", w);
    dl_text(bd, 80, 120, 1,dl_color_from_name("black"), 2);
    dl_text(wd, 450, 120, 1,dl_color_from_name("white"), 2);
    dl_circle(65, 115, 8,dl_color_from_name("black"), 1, 1);
    dl_circle(435, 115, 8,dl_color_from_name("white"), 1, 1);
    for (cr = 460; cr > 331; cr -= 0.01) dl_circle(320, 250, cr,dl_color_from_rgb(125, 125, 125), 0.5, 0);
  }
  
  while (1) {
    dl_wait(0.01);
  }
  
  return 0;
}
