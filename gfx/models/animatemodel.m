function animatemodel(fn,w,h,offs,len)

a = imread(fn);

x = 0;
while(1)
  imagesc(a(offs*h+1:offs*h+h,x+1:x+w,:));
  axis image;
  drawnow;
  x = x + w;
  if( x > (len*w-1) )
    x = 0;
  end;
  pause(0.05);
end;