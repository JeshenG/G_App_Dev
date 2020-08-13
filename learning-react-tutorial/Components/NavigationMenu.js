import React from 'react'
import {Link} from "react-router-dom";

//The prop that is passed in is a function that will close the menu
function NavigationMenu(props) {
    return (
        <div>
            <div className="font-bold py-3">
                React App 
            </div>

            <ul>
                <li>
                    {/*props are attributes*/}
                    <Link to="/" className="text-blue-500 py-3 border-t border-b block" onClick={props.closeMenu}>Home</Link>
                </li>
                <li>
                    {/*If we click on this link the url should change*/}
                    <Link to="/about" className="text-blue-500 py-3 border-b block" onClick={props.closeMenu}>About</Link>
                </li>
            </ul>
        </div>
    )
}

export default NavigationMenu;