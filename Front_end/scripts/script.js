$(document).ready(function(){

    $(".right").on("click",function(e){
    
        var one = $('.b40')[0].innerHTML;
         var two = $('.b44')[0].innerHTML;
        var three = $('.b43')[0].innerHTML;
        var four = $('.b42')[0].innerHTML;
        var five = $('.b45')[0].innerHTML;
             
          $('.b40')[0].innerHTML=four;
        
         
          
        
          $('.b44')[0].innerHTML=one; 
          $('.b43')[0].innerHTML=two;   
          $('.b42')[0].innerHTML=five; 
          $('.b45')[0].innerHTML=three; 
        
        e.stopPropagation();
 
     
    })
     
  
       $(".left").on("click",function(e){
    
        var one = $('.b40')[0].innerHTML;
         var two = $('.b44')[0].innerHTML;
        var three = $('.b43')[0].innerHTML;
        var four = $('.b42')[0].innerHTML;
        var five = $('.b45')[0].innerHTML;
             
          $('.b40')[0].innerHTML=two; 
          $('.b44')[0].innerHTML=five
           ; 
             $('.b43')[0].innerHTML=four;   
        $('.b42')[0].innerHTML=one; 
          $('.b45')[0].innerHTML=three; 
        
        e.stopPropagation();

     
    })


    
    
    
    
     $(".arrow_right").on("click",function(e){
    
         var aone = $('.b61')[0].innerHTML;
         var aaone=$('.b61').css("background-color");
         
         var atwo = $('.b62')[0].innerHTML;
         var aatwo=$('.b62').css("background-color");
         
        var athree = $('.b63')[0].innerHTML;
         var aathree=$('.b63').css("background-color");
         
        var afour = $('.b64')[0].innerHTML;
         var aafour=$('.b64').css("background-color");
         
        var afive = $('.b65')[0].innerHTML;
         var aafive=$('.b65').css("background-color");
             
          $('.b65')[0].innerHTML=afour; 
         
         $('.b65').css("background-color",aafour);
          
        
          $('.b64')[0].innerHTML=athree; 
         $('.b64').css("background-color",aathree);
         
         
          $('.b63')[0].innerHTML=atwo;   
         $('.b63').css("background-color",aatwo);
         
          $('.b62')[0].innerHTML=aone;
         $('.b62').css("background-color",aaone);
         
          $('.b61')[0].innerHTML=afive;
         $('.b61').css("background-color",aafive);
        
        e.stopPropagation();
    
    
     })
    
    
    
    
    $(".arrow_left").on("click",function(e){
    
         var aone = $('.b61')[0].innerHTML;
         var aaone=$('.b61').css("background-color");
         
         var atwo = $('.b62')[0].innerHTML;
         var aatwo=$('.b62').css("background-color");
         
        var athree = $('.b63')[0].innerHTML;
         var aathree=$('.b63').css("background-color");
         
        var afour = $('.b64')[0].innerHTML;
         var aafour=$('.b64').css("background-color");
         
        var afive = $('.b65')[0].innerHTML;
         var aafive=$('.b65').css("background-color");
             
          $('.b65')[0].innerHTML=aone; 
         
         $('.b65').css("background-color",aaone);
          
        
          $('.b64')[0].innerHTML=afive; 
         $('.b64').css("background-color",aafive);
         
         
          $('.b63')[0].innerHTML=afour;   
         $('.b63').css("background-color",aafour);
         
          $('.b62')[0].innerHTML=athree;
         $('.b62').css("background-color",aathree);
         
          $('.b61')[0].innerHTML=atwo;
         $('.b61').css("background-color",aatwo);
        
        e.stopPropagation();
    
    
     })
    
    
    
})