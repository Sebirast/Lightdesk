
/* -*- C++ -*- */
/********************
Sept. 2014 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com

Use graphics screens (adafruit library based) as menu output
www.r-site.net

***/
#ifndef RSITE_ARDUINOP_MENU_GFX
	#define RSITE_ARDUINOP_MENU_GFX
	#include <Adafruit_GFX.h>
	#include "../menuDefs.h"
    #include <Adafruit_RA8875.h>

namespace Menu {

		#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

	  class adaGfxOut:public gfxOut {
	    public:
				Adafruit_RA8875& gfx;
				const colorDef<uint16_t> (&colors)[nColors];
		    adaGfxOut(Adafruit_RA8875& gfx,const colorDef<uint16_t> (&c)[nColors],idx_t* t,panelsList &p,idx_t resX=6,idx_t resY=9)
					:gfxOut(resX,resY,t,p),gfx(gfx),colors(c) {}
					//:gfxOut(gfx.width()/resX,gfx.height()/resY,resX,resY,false),colors(c),gfx(gfx) {}

				size_t write(uint8_t ch) override {
                    gfx.textMode();
                    return gfx.write(ch);
                    }

				inline uint16_t getColor(colorDefs color=bgColor,bool selected=false,status stat=enabledStatus,bool edit=false) const {
          return memWord(&(stat==enabledStatus?colors[color].enabled[selected+edit]:colors[color].disabled[selected]));
        }

				void setColor(colorDefs c,bool selected=false,status s=enabledStatus,bool e=false) override {
					gfx.textTransparent(getColor(c,selected,s,e));
				}

				void clearLine(idx_t ln,idx_t panelNr=0,colorDefs color=bgColor,bool selected=false,status stat=enabledStatus,bool edit=false) override {
					const panel p=panels[panelNr];
					gfx.fillRect(p.x*resX,(p.y+ln)*resY,p.maxX()*resX,resY,getColor(color,selected,stat,edit));
		    	//setCursor(0,ln);
		    }
		    void clear() override {
					panels.reset();
					gfx.fillScreen(getColor(bgColor,false,enabledStatus,false));
		    	setCursor(0,0);
					setColor(fgColor);
				}

				void box(idx_t panelNr,idx_t x,idx_t y,idx_t w=1,idx_t h=1,colorDefs c=bgColor,bool selected=false,status stat=enabledStatus,bool edit=false) override {
					const panel p=panels[panelNr];
					gfx.drawRect((p.x+x)*resX,(p.y+y)*resY,w*resX,h*resY,getColor(c,selected,stat,edit));
				}

				void rect(idx_t panelNr,idx_t x,idx_t y,idx_t w=1,idx_t h=1,colorDefs c=bgColor,bool selected=false,status stat=enabledStatus,bool edit=false) override {
					const panel p=panels[panelNr];
					gfx.fillRect((p.x+x)*resX,(p.y+y)*resY,w*resX,h*resY,getColor(c,selected,stat,edit));
				}

				void clear(idx_t panelNr) override {
					const panel p=panels[panelNr];
					gfx.fillRect(p.x*resX,p.y*resY,p.w*resX,p.h*resY,getColor(bgColor,false,enabledStatus,false));
					panels.nodes[panelNr]=NULL;
				}

		    void setCursor(idx_t x,idx_t y,idx_t panelNr=0) override {
					const panel p=panels[panelNr];
					gfx.textSetCursor((p.x+x)*resX,(p.y+y)*resY+fontMarginY);
				}

				void drawCursor(idx_t ln,bool selected,status stat,bool edit=false,idx_t panelNr=0) override {
					const panel p=panels[panelNr];
					// gfxOut::drawCursor(ln,selected,stat);
					gfx.drawRect(p.x*resX,(p.y+ln)*resY,maxX()*resX,resY,getColor(cursorColor,selected,enabledStatus,false));
				}
	  };

}; //namespace adaGfxOut
#endif