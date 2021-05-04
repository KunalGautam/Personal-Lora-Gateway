function setSelectedIndex(s, valsearch) {
    if (valsearch == "Asia/Calcutta") { // Safari fix
        valsearch = "Asia/Kolkata";
    }
// Loop through all the items in drop down list
    for (i = 0; i < s.options.length; i++) {
        if (s.options[i].value == valsearch) {
// Item is found. Set its property and exit
            s.options[i].selected = true;
            break;
        }
    }
    return;
}

setSelectedIndex(document.getElementById("timeZoneSelect"), Intl.DateTimeFormat().resolvedOptions().timeZone);