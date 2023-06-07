import React, { useEffect, useState } from 'react';



function Time() {

  const [cur, setcur] = useState(0)

  useEffect(() => {

  }, [])


  window.setTimeout(() => {
    setcur(cur + 1)
  }, 1000)

  return (
    <div className="time">
      <p> {cur} seconde</p>
    </div>
  );

}



export default Time;