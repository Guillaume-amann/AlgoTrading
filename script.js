window.addEventListener('scroll', function() {
    let scrollPosition = window.scrollY;
    let header = document.querySelector('header');
    header.style.top = -(scrollPosition * 1000) + 'px'; // Adjust speed of scroll effect
});